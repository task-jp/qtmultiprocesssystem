requires(qtHaveModule(quick))
load(qt_parts)
OTHER_FILES = .qmake.conf sync.profile
load(configure)
qtCompileTest(systemd_watchdog)
