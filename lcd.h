void WriteLCD(unsigned char  anyByte);
void cmdLCD(unsigned char cmd);
void charLCD(unsigned char asciiVal);
void StrLCD(char *p);
void InitLCD(void);
void U32LCD(unsigned int num);
void S32LCD(int Snum);
void F32LCD(float fNum,unsigned char nDP);
void BuidCGRAM(unsigned char *p, unsigned char nBytes);
