namespace perennial{
	namespace randomgen{
		namespace perlinlike{
			//3 Layers, fancy!
			
			//PURPOSE: Generate a 1D array of Perlin-like Noise.
			//Taken from https://www.youtube.com/watch?v=6-0UaeJBumA , but with different variable names.
			float *f_generatePerlin1D(int iOutputSize, float *fSeed, int iOctaves)
			{
				float *fOutput;
				for(int iX = 0; iX < iOutputSize; iX++)
				{
					float fNoise = 0.0f;
					float fScale = 1.0f;
					float fScaleAcc = 0.0f;

					for (int iO = 0; iO < iOctaves; iO++)
					{
						int iPitch = iOutputSize >> iO;
						int iSample1 = (iX / iPitch) * iPitch;
						int iSample2 = (iSample1 + iPitch) % iOutputSize;

						float fBlend = (float)(iX - iSample1) / (float)iPitch;
						float fSample = (1.0f - fBlend) * fSeed[iSample1] + fBlend * fSeed[iSample2];
						fNoise += fSample * fScale;

						fScaleAcc += fScale;
						fScale = fScale/2.0f;
					}
					fOutput[iX] = fNoise / fScaleAcc;
				}

				return fOutput;
			}
		}
	}
}