#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <fstream>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

bool stop = false;

static unsigned __int32 popcnt(unsigned __int64 a)
{
	static const unsigned __int64 m1 = 0x5555555555555555;
	static const unsigned __int64 m2 = 0x3333333333333333;
	static const unsigned __int64 m4 = 0x0f0f0f0f0f0f0f0f;
	a -= (a >> 1) & m1;
	a = (a & m2) + ((a >> 2) & m2);
	a = (a + (a >> 4)) & m4;
	a += a >> 8;
	a += a >> 16;
	a += a >> 32;
	return (unsigned __int32)(a & 0x7f);
}

static unsigned __int64 tolong(const char *buf)
{
	return *((unsigned __int64*)buf);
}

static uint64_t _s[2];

static uint64_t xorshift64star(uint64_t s[1])
{
	uint64_t x = s[0];
	x ^= x >> 12;
	x ^= x << 25;
	x ^= x >> 27;
	s[0] = x;
	return x * UINT64_C(0x2545f4914f6cdd1d);
}

static uint64_t xoroshiro128plus(uint64_t s[2])
{
	uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	uint64_t result = s0 + s1;
	s1 ^= s0;
	s[0] = ((s0 << 55) | (s0 >> 9)) ^ s1 ^ (s1 << 14);
	s[1] = (s1 << 36) | (s1 >> 28);
	return result;
}

static unsigned __int64 rand_uint64(void)
{
	return (unsigned __int64)xoroshiro128plus(_s);
}

// unsigned __int32 range from 0 to 4294967295
// unsigned __int64 range from 0 to 18446744073709551615

#define BYTE_SIZE_BITS 8
#define LONG_SIZE_BYTES sizeof(unsigned __int64)
#define EXPERIMENT_COUNT_BYTES 1024
#define LOOP_COUNT_EXPERIMENTS 16
#define LONG_SIZE_BITS (LONG_SIZE_BYTES * BYTE_SIZE_BITS)

static void trand_buf(char* buf)
{
	const char* fileName = "data.bin";
	while (true)
	{
		bool ok = true;
		memset(buf, 0, EXPERIMENT_COUNT_BYTES);
		FILE* fp = _fsopen(fileName, "rb", _SH_DENYWR);
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_SET);
			size_t bytesRead = fread(buf, 1, EXPERIMENT_COUNT_BYTES, fp);
			if (bytesRead != EXPERIMENT_COUNT_BYTES)
			{
				ok = false;
			}
			FILE* tmp_fp;
			errno_t err = freopen_s(&tmp_fp, fileName, "wb", fp);
			if (err != 0 || tmp_fp == NULL)
			{
				// Silently handle error, no need to print
			}
			fclose(fp);
		}
		else
		{
			// File could not be opened, likely because QRNG.exe is writing to it
			ok = false;
		}
		if (ok == true)
		{
			break;
		}
		Sleep(1 * 1000); 
	}
}

static unsigned __int64 trand_uint64(char *buf, unsigned __int32 j)
{
	return tolong(&(buf[j]));
}

static void fprintf_date(FILE *fp, time_t utime)
{
	char tbuff[256];
	struct tm tmdest;
	gmtime_s(&tmdest, &utime);
	asctime_s(tbuff, sizeof(tbuff), &tmdest);
	if (tbuff[8] == ' ')
		tbuff[8] = '0';
	tbuff[strlen(tbuff) - 1] = '\0';
	fprintf(fp, "%s", tbuff);
	fflush(fp);
}

static void signal_handler(int n_signal)
{
	stop = true;
}

static void random_seed()
{
	_s[0] = (uint64_t)time(NULL);
	_s[1] = xorshift64star(&_s[0]);
}

/**
<summary>Main entry point for the RGNG.exe application.
Reads random data from the local file 'data.bin', regardless of how the file was populated (by QRNG.exe or otherwise).
Simulates a series of coin tosses and performs statistical analysis, including calculating Shannon Eta entropy.
The results of the experiment are written to console and output files 'TRNG.txt' (quantum random data) and 'PRNG.txt' (pseudo-random data).</summary>
*/
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		fprintf(stderr, "Arguments ignored\n");
	}
	signal(SIGINT, &signal_handler);
	const unsigned __int32 experiments = LOOP_COUNT_EXPERIMENTS;
	const unsigned __int32 tosses = (LONG_SIZE_BITS * EXPERIMENT_COUNT_BYTES / LONG_SIZE_BYTES);
	if (tosses > 4294967295)
	{
		fprintf(stderr, "Number of tosses per experiment exceeded: %d\n", 4294967295);
	}
	random_seed();
	FILE* fp = _fsopen("TRNG.txt", "at", _SH_DENYWR);
	if (fp == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", "TRNG.txt");
		return 1;
	}
	FILE* fpp = _fsopen("PRNG.txt", "at", _SH_DENYWR);
	if (fpp == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", "PRNG.txt");
		return 1;
	}
	time_t utime0 = time(NULL);
	fprintf_date(stdout, utime0);
	fprintf(stdout, "  ...\n");
	fflush(stdout);
	while (true)
	{
		time_t utime1, utime2;
		double s[LOOP_COUNT_EXPERIMENTS], sp[LOOP_COUNT_EXPERIMENTS];
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			if (k == 0)
			{
				utime1 = time(NULL);
				fprintf_date(stdout, utime1);
				printf("  %04u %07u\n", 0, tosses);
				fflush(stdout);
			}
			unsigned __int32 n = 0, f = 0, fp = 0;
			char buf[EXPERIMENT_COUNT_BYTES];
			trand_buf(buf);
			for (int i = 0; i < EXPERIMENT_COUNT_BYTES; i += LONG_SIZE_BYTES)
			{
				unsigned __int64 r = trand_uint64(buf, i);
				f += popcnt(r);
				unsigned __int64 rp = rand_uint64();
				fp += popcnt(rp);
				n += LONG_SIZE_BITS;
			}
			double p = ((double)f) / ((double)n);
			double q = 1. - p;
			double e = (p == 0 || q == 0) ? 0. : -p * log2(p) - q * log2(q);
			double pp = ((double)fp) / ((double)n);
			double qp = 1. - pp;
			double ep = (pp == 0 || qp == 0) ? 0. : -pp * log2(pp) - qp * log2(qp);
			fprintf(stderr, "%04u %07u %07u %07u %.6f %.6f %.6f %.6f %.8f %.8f\n", k + 1, f, fp, n, p, pp, q, qp, e, ep);
			s[k] = e;
			sp[k] = ep;
			if (k == LOOP_COUNT_EXPERIMENTS - 1)
			{
				utime2 = time(NULL);
			}
			if (stop == true)
			{
				break;
			}
		}
		if (stop == true)
		{
			fflush(stdout);
			time_t utime3 = time(NULL);
			fprintf_date(stdout, utime3);
			fprintf(stdout, "\n");
			fflush(stdout);
			break;
		}
		double sm = 0., ss = 0.;
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			sm += s[k];
		}
		sm = sm / ((double)experiments);
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			double ads = abs(s[k] - sm);
			ss += ads * ads;
		}
		ss = sqrt(ss / ((double)experiments - 1.));
		double sl = 1., sh = 0.;
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			sl = min(sl, s[k]);
			sh = max(sh, s[k]);
		}
		double smp = 0., ssp = 0.;
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
			smp += sp[k];
		smp = smp / ((double)experiments);
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			double adsp = abs(sp[k] - smp);
			ssp += adsp * adsp;
		}
		ssp = sqrt(ssp / ((double)experiments - 1.));
		double slp = 1., shp = 0.;
		for (unsigned __int32 k = 0; k < LOOP_COUNT_EXPERIMENTS; k++)
		{
			slp = min(slp, sp[k]);
			shp = max(shp, sp[k]);
		}
		double t = (double)(utime2 - utime1);
		fprintf_date(stdout, utime2);
		printf("  %04u %07u %09.0f %.8f %.8f %.8f %.8f %.8f %.8f %.8f %.8f\n", experiments, tosses, t, sm, smp, sm - 3.*ss, smp - 3. * ssp, sh, sl, shp, slp);
		fflush(stdout);
		fprintf(fp, "['");
		fprintf_date(fp, utime2);
		fprintf(fp, "', %.8f", sm);
		fprintf(fp, ", %.8f", sm - 3. * ss);
		fprintf(fp, ", %.8f", sh);
		fprintf(fp, ", %.8f],\n", sl);
		fflush(fp);
		fprintf(fpp, "['");
		fprintf_date(fpp, utime2);
		fprintf(fpp, "', %.8f", smp);
		fprintf(fpp, ", %.8f", smp - 3. * ssp);
		fprintf(fpp, ", %.8f", shp);
		fprintf(fpp, ", %.8f],\n", slp);
		fflush(fpp);
	}
	if (fp != NULL)
	{
		fclose(fp);
	}
	if (fpp != NULL)
	{
		fclose(fpp);
	}
	return 0;
}

