void init()
{
	const char hello[] = "Hello World!\n";
	int i;
	char *video = (char*) 0xb8000;

	// bis null terminator erreicht ist
	for (i = 0; hello[i] != '\0'; i++) {
		video[i * 2] = hello[i];
		// 0x07 hellgrau auf schwarz
		video[i * 2 + 1] = 0x07;
	}
}
