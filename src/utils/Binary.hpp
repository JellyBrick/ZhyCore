#ifndef bin
#define bin
static char *writeLong(__int64 v) {
	static char res[8];

		res[0] = ((char)((v >> 56) & 0xFF));
		res[1] = ((char)((v >> 48) & 0xFF));
		res[2] = ((char)((v >> 40) & 0xFF));
		res[3] = ((char)((v >> 32) & 0xFF));
		res[4] = ((char)((v >> 24) & 0xFF));
		res[5] = ((char)((v >> 16) & 0xFF));
		res[6] = ((char)((v >>  8) & 0xFF));
		res[7] = ((char)((v) & 0xFF));
		return res;
	}

#endif
