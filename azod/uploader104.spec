# -*- mode: python -*-
a = Analysis(['uploader104.py'],
             pathex=['C:\\Users\\lesul_000\\Documents\\GitHub\\herding\\azod'],
             hiddenimports=[],
             hookspath=None,
             runtime_hooks=None)
pyz = PYZ(a.pure)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='uploader104.exe',
          debug=False,
          strip=None,
          upx=True,
          console=False , icon='dragon.ico')
