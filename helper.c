#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <sys/file.h>
#include <unistd.h>
#endif

#ifdef _WIN32
static int aquire_lock (char *lock_file) {
  HANDLE fd = CreateFileA(lock_file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (fd == INVALID_HANDLE_VALUE) return -1;

  while (1) {
    int locked = LockFile(fd, 0, 0, 1, 0) ? 1 : 0;
    Sleep(1000);
    if (locked == 1) return 0;
  }
}
#else
static int aquire_lock (char *lock_file) {
  int fd = open(lock_file, O_RDONLY);

  if (fd < 0) return -1;

  while (1) {
    int locked = flock(fd, LOCK_EX | LOCK_NB) == 0 ? 1 : 0;
    sleep(1);
    if (locked == 1) return 0;
  }
}
#endif

// for windows in case lock is released early
static int rename_retry (char *old, char *new) {
  for (int i = 0; i < 4; i++) {
    if (!rename(old, new)) return 0;
#ifdef _WIN32
    Sleep(2000);
#else
    sleep(2);
#endif
  }
  return -1;
}

int main (int argc, char **argv) {
  if (argc < 6) {
    printf("Usage: %s <lock_file> <new_version_path> <app_path> <tmp_app_path> <exec_path> ...argv\n", argv[0]);
    return 1;
  }

  char *lock_file = *(++argv);
  char *new_version_path = *(++argv);
  char *app_path = *(++argv);
  char *tmp_path = *(++argv);
  char *exec_path = *(++argv);

  if (aquire_lock(lock_file)) return 2;

  if (rename_retry(new_version_path, tmp_path)) return 3;
  if (rename_retry(app_path, new_version_path)) return 4;
  if (rename_retry(tmp_path, app_path)) return 5;

  return execv(exec_path, argv);
}
