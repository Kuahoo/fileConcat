
int fileOpener(char *fileToOpen);

int fileReader(int fileToRead, char *buffer[]);

int fileWriter(char *buffer[]);

int fileCloser(int fileToClose);

void toStdout(int fileDescriptor, char *buffer[]);
