/*Macro Definition*/
#define Sqr(x)	((x)*(x))
#define Cube(x)	((x)*(x)*(x))
#define DO_MOL	for (n = 0; n < nMol; n ++)
//C supports the use of macro definitions that can simplify the code considerably.

#define VAdd(v1, v2, v3)	//Vector addition, 2D
	(v1).x = (v2).x + (v3).x,
	(v1).y = (v2).y + (v3).y

#define VSAdd(v1, v2, s3, v3)
	(v1).x = (v2).x + (s3) * (v3).x,
	(v1).y = (v2).y + (s3) * (v3).y
#define VVSAdd(v1, s2, v2) VSAdd (v1, v1, s2, v2)

#define VSub(v1, v2, v3)	//Vector Subtraction, 2D
	(v1).x = (v2).x - (v3).x,
	(v1).y = (v2).y - (v3).y

#define VDot(v1, v2)
	((v1).x * (v2).x + (v1).y * (v2).y)
#define VLenSq(v)	VDot(v, v)		//x*x+y*y
	
#define VSet(v, sx, sy)
	(v).x = sx,
	(v).y = sy
#define VSetAll(v, s)	VSet(v, s, s)
#define VZero(v)		VSetAll(v, 0)

	
#define VWrap(v, t)
	if (v.t >= 0.5 * region.t) v.t -= region.t;
	else if (v.t < -0.5 * region.t) v.t += region.t
#define VWrapAll(v)		//2D
	{VWrap (v, x);
	VWrap (v, y);}
	


void main()
{
		
}

typedef double real;

//vector structure
typedef struct{
	real x, y;
} VecR;

typedef struct{
	int x, y;
} VecI;			//intergal initial cell vector to compute atom number

//Atom Structure
typedef struct{
	VecR r, rv, ra;
} Mol;

typedef struct{
	real val, sum, sum2;	//value, sum, and sum of squares
} Prop;	

//Global variables
Mol *mol;
VecR region, vSum;
VecI initUcell;
Prop kinEnergy, pressure, totEnergy;
real deltaT, density, rCut, temperature, timeNow, uSum, velMag,
	virSum, vvSum;
int moreCycles, nMol, stepAvg, stepCount, stepEquil, stepLimit;

real rCut;		//soft-sphere interaction range, rc


void ComputeForces ()
{
	VecR dr;
	real fcVal, rr, rrCut, rri, rri3;
	int j1, j2, n;
	
	rrCut = Sqr (rCut);
	DO_MOL VZero(mol[n].ra);	//set a to zero
	uSum = 0.;
	virSum = 0.;
	for(j1 = 0; j1 < nMol - 1; j1 ++){
		for(j2 = j1 + 1; j2 < nMol; j2 ++){
			VSub (dr, mol[j1].r, mol[j2].r);
			VWrapAll(dr);
			rr = VLenSq (dr);
			if(rr < rrCut){			//within rc
				rri = 1. / rr;
				rri3 = Cube (rri);
				fcVal = 48. * rri3 * (rri3 - 0.5) * rri;
				VVSAdd(mol[j1].ra, fcVal, dr);
				VVSAdd(mol[j2].ra, - fcVal, dr);
				uSum += 4. * rri3 * (rri3 - 1.) + 1.;
				virSum += fcVal * rr;
			}
		}
	}
	
}




