#include "barrett.h"
static uint32_t m_val[75] = { 243079, 243093, 243106, 243120, 243134, 243148, 243161, 243175, 243189, 243203, 243216, 243230, 243244, 243258, 243272, 243285, 243299, 243313, 243327, 243340, 243354, 243368, 243382, 243396, 243409, 243423, 243437, 243451, 243465, 243478, 243492, 243506, 243520, 243534, 243547, 243561, 243575, 243589, 243603, 243616, 243630, 243644, 243658, 243672, 243686, 243699, 243713, 243727, 243741, 243755, 243769, 243782, 243796, 243810, 243824, 243838, 243852, 243865, 243879, 243893, 243907, 243921, 243935, 243949, 243962, 243976, 243990, 244004, 244018, 244032, 244046, 244059, 244073, 244087, 244101 };

void boolean_refresh_32(uint32_t *x)
{
	int i, j;
	for(i = 0; i <= D; ++i)
	{
		for(j = 1; j <= D; ++j)
		{
		  uint32_t r = (uint32_t) next();
			x[0] ^= r;
			x[j] ^= r;
		}
	}
}

void boolean_sec_and_32(uint32_t *x, uint32_t *y, uint32_t *z)
{
	for(int i = 0; i <= D; ++i)
		z[i] = x[i] & y[i];

	for(int i = 0; i <= D; ++i)
	{
		for(int j = i+1; j <= D; ++j)
		{
		  uint32_t r = (uint32_t) next();
			z[i] ^= r;
			r ^= x[i] & y[j];
			r ^= x[j] & y[i];
			z[j] ^= r;
		}
	}
}

void convert_64to32(uint64_t x[D+1], uint32_t r[D+1]){
  for(int d=0; d<= D; ++d){
    r[d] = x[d];
  }
}

void convert_32to64(uint32_t x[D+1], uint64_t r[D+1]){
  for(int d=0; d<= D; ++d){
    r[d] = x[d];
  }
}


void boolean_demi_sec_plus_32(uint32_t x[D+1], uint32_t y, uint32_t z[D+1])
{
  uint32_t p[D+1];
  for(int i = 0; i <= D; ++i)
    {
      p[i] = (uint32_t) x[i];
    }
  p[0] ^= y;

  uint32_t g[D+1];
  for(int d = 0; d <= D; ++d)
    g[d] = x[d] & y;

  uint32_t a[D+1];

  uint8_t w = 5;

  for(int j = 0; j < w; ++j)
    {
      uint8_t pow = 1 << j;
      uint32_t a1[D+1];
      for(int i = 0; i <= D; ++i)
	{
	  a[i] = g[i] << pow;
	  a1[i] = p[i] << pow;
	}

      uint32_t t[D+1];
      boolean_sec_and_32(a, p, t);
      for(int i = 0; i <= D; ++i)
	{
	  a[i] = t[i];
	  g[i] ^= a[i];
	}

      boolean_refresh_32(a1);
      boolean_sec_and_32(p, a1, t);
      for(int i = 0; i <= D; ++i)
	p[i] = t[i];

    }
  for(int i = 0; i <= D; ++i)
    a[i] = g[i] << (1 << w);

  uint32_t t[D+1];
  boolean_sec_and_32(a, p, t);

  g[0] ^= t[0];
  z[0] = x[0] ^ y ^ (g[0] << 1);

  for(int i = 1; i <= D; ++i)
    {
      g[i] ^= t[i];
      z[i] = x[i] ^ (g[i] << 1);
    }
}

void boolean_demi_sec_equality_32(uint32_t x[D+1], uint32_t y, uint32_t z[D+1])
{
	for(int d = 0; d<=D; ++d)
	  z[d] = x[d];
	z[0] ^= y;

	for(int k = 16; k != 0; k /= 2)
	{
		uint32_t a[D+1], b[D+1];
		for(int d = 0; d<=D; ++d)
		{
			a[d] = z[d] & (((uint32_t)1 << k) - 1);
			b[d] = (z[d] >> k);
		}

		a[0] ^= (((uint32_t)1 << k) - 1);
		b[0] ^= (((uint32_t)1 << k) - 1);

		boolean_sec_and_32(a, b, z);

		z[0] ^= (((uint32_t)1 << k) - 1);
	}
}

void boolean_sec_minus(uint64_t a[D+1], uint64_t b[D+1], uint64_t r[D+1]){
  uint64_t nb[D+1], mb[D+1];
  for(int d =0; d<=D; ++d){
    nb[d] = b[d];
  }
  nb[0] = ~b[0];
  boolean_demi_sec_plus(nb, 1, mb);
  boolean_sec_plus(a,mb,r);

}

void sec_if_32(uint32_t a[D+1], uint32_t b[D+1], uint32_t c[D+1], uint32_t res[D+1])
{
	uint32_t t[D+1], t1[D+1];
	for(int d = 0; d<=D; ++d)
		t[d] = (c[d] & 1) * (uint64_t)(-1);


	boolean_sec_and_32(a, t, res);
	t[0] ^= (uint32_t)(-1);
	boolean_sec_and_32(b, t, t1);

	for(int d = 0; d<=D; ++d)
		res[d] ^= t1[d];
}


void barrett(uint64_t a[D+1], uint8_t i, uint32_t r[D+1]){
	uint64_t q[D+1]={0};
	uint64_t qn[D+1]={0};
	uint64_t a_qn[D+1]={0};
	uint32_t a_qn32[D+1]={0};
	uint32_t A[D+1]={0};
	uint32_t z[D+1]={0};
	uint32_t t[D+1]={0};

	uint32_t n = 17669 - i;

	// q = (a * m) >> k
	boolean_demi_mult(a, m_val[i], q, 17);
	for(int j=0; j<=D;j++){
		q[j] >>= 32;
	}

	boolean_demi_mult(q, n, qn, 14);
	boolean_refresh(a);
	boolean_sec_minus(a, qn, a_qn);



	for(int j=0; j<=D;j++){
		a_qn[j] &= moins1;
	}

	// Conditional subtraction
	uint32_t minus_n = (1<<32) - n;
	convert_64to32(a_qn, a_qn32);


	boolean_demi_sec_plus_32(a_qn32, minus_n, A);



	for(int j=0; j<=D;j++){
			z[j] = A[j]>> 31;
	}

	boolean_demi_sec_equality_32(z, 1, t);
	boolean_refresh_32(a_qn32);
	sec_if_32(A, a_qn32, t, r);
	

}


// Fisher-Yates adapted to HQC
void fy_hqc(uint64_t x[][D+1], uint16_t s, uint64_t n, uint16_t bits){
	for(int i = s - 1; i >= 0; --i)
			{
				uint64_t val_i[D+1]={0};
				val_i[0] = i;
				boolean_refresh(val_i);
				uint32_t r32[D+1];
				uint64_t r[D+1];
				barrett(x[i],i,r32);
				convert_32to64(r32, r);
				boolean_demi_sec_plus(r, i, x[i]);

				for(int j = i + 1; j < s; ++j)
				{
					uint64_t temp[D+1]={0}, temp1[D+1]={0};
					sec_equality(x[i], x[j], temp);

					sec_if(x[i], val_i, temp, temp1);
					memcpy(x[i], temp1, 8*(D+1));
				}
			}
}
