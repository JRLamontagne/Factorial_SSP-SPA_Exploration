#include "CDICE.h"
//===========================================================================================
// InitializeDICE(DICE *dice, char *parms[]) 
//
// Defines and allocate Config, Endog, and Ref variables.
//
// Return ()
// - 'dice' structure variables are updated
//===========================================================================================
void InitilizeDICE(DICE *dice)
{
	// Time series ---------------------------------
	dice->config.nPeriods = 60;		// Number of time steps
	dice->config.tstep = 5;		// Number of years per time step
	dice->config.startYear = 2010;	// Model start year
	
	// Allocate time-series variables ----------------
	// Exogenous variables	
	dice->config.dateSeries = new double[dice->config.nPeriods];	// Human-readable year
	dice->config.l = new double[dice->config.nPeriods];			// Level of population and labor (millions)
	dice->config.al = new double[dice->config.nPeriods];			// Level of total factor productivity
	dice->config.sigma = new double[dice->config.nPeriods];		// CO2-equivalent-emissions output ratio 
	dice->config.rr  = new double [dice->config.nPeriods];			// Average utility social discount rate
	dice->config.ga = new double[dice->config.nPeriods];			// Growth rate of productivity from (sic)
	dice->config.forcoth = new double[dice->config.nPeriods];		// Exogenous forcing for other GHG
	dice->config.gl = new double[dice->config.nPeriods];			// Growth rate of labor
	dice->config.gcost = new double[dice->config.nPeriods];		// Growth of cost factor
	dice->config.gsig = new double[dice->config.nPeriods];			// Change in sigma (cumulative improvement of energy efficiency)
	dice->config.etree = new double[dice->config.nPeriods];		// Emissions from deforestation
	dice->config.cost1 = new double[dice->config.nPeriods];		// Adjusted cost for backup
	dice->config.partfract = new double[dice->config.nPeriods];		// Fraction of emissions in control regime
	//dice->config.gfacpop = new double[dice->config.nPeriods];		// Growth factor population (Appears in GAMS version, but never used
	dice->config.pbacktime = new double[dice->config.nPeriods];		// Backstop price
	dice->config.scc = new double[dice->config.nPeriods];			// Social cost of carbon
	dice->config.cpricebase = new double[dice->config.nPeriods];	// Carbon price in base case
	dice->config.photel = new double[dice->config.nPeriods];		// Carbon price under no damages (Hotelling rent condition)
	
	dice->config.miu_up = new double[dice->config.nPeriods];		// Upper limit of control policy for each time period
	

	// Endogenous variables
	dice->endog.miu = new double[dice->config.nPeriods];			// Emission control rate GHGs
	dice->endog.forc = new double[dice->config.nPeriods];			// Increase in radiative forcing [Wm-2 from 1900]
	dice->endog.tatm = new double[dice->config.nPeriods];			// Increase temperature of atmosphere [dC from 1900]
	dice->endog.tocean = new double[dice->config.nPeriods];		// Increase temperature of lower oceans [dC from 1900]
	dice->endog.mat = new double[dice->config.nPeriods];			// Carbon concentration increase in atmosphere [GtC from 1750]
	dice->endog.mu = new double[dice->config.nPeriods];			// Carbon concentration increase in shallow oceans [GtC from 1750]
	dice->endog.ml = new double[dice->config.nPeriods];			// Carbon concentration increase in lower oceans [GtC from 1750]
	dice->endog.e = new double[dice->config.nPeriods];			// Total CO2 emissions [GtCO2 per year]
	dice->endog.eind = new double[dice->config.nPeriods];			// Industrial emissions [GtCO2 per year]
	dice->endog.c = new double[dice->config.nPeriods];			// Consumption [Trillions 2005 US$ per year]
	dice->endog.k = new double[dice->config.nPeriods];			// Capital stock [Trillions 2005 US$]
	dice->endog.cpc = new double[dice->config.nPeriods];			// Per capita consumption [Thousands 2005 US$ per year]
	dice->endog.i = new double[dice->config.nPeriods];			// Investment [trillions 2005 US$ per year]
	dice->endog.s = new double[dice->config.nPeriods];			// Gross savings rate as function of gross world production
	dice->endog.ri = new double[dice->config.nPeriods];			// Real interest rate (per annum)
	dice->endog.y = new double[dice->config.nPeriods];			// Gross world product net of abatement and damages [Trillions 2005 US$ per year]
	dice->endog.ygross = new double[dice->config.nPeriods];		// Gross world product GROSS of abatement and damages [Trillions 2005 US$ per year]
	dice->endog.ynet = new double[dice->config.nPeriods];			// Output net of damages equation [Trillions of 2005 US$ per year]
	dice->endog.damages = new double[dice->config.nPeriods];		// Damages [Trillions 2005 US$ per year]
	dice->endog.damfrac = new double[dice->config.nPeriods];		// Damages as fraction of gross output
	dice->endog.abatecost = new double[dice->config.nPeriods];		// Cost of emissions reductions [Trillions 2005 US$ per year]
	dice->endog.mcabate = new double[dice->config.nPeriods];		// Marginal cost of abatement [2005 US$ per ton CO2]
	dice->endog.cca = new double[dice->config.nPeriods];			// Cumulative industrial carbon emissions [GtC]
	dice->endog.periodu = new double[dice->config.nPeriods];		// One period utility function
	dice->endog.cprice = new double[dice->config.nPeriods];		// Carbon price [2005 US$ per ton CO2]
	dice->endog.cemutotper = new double[dice->config.nPeriods];		// Period utility
	
	// *** Additional parameters *** ------------------------------------------
	// Define, allocate, and initialize additional objectives and parameters.
	// Initialize any additional parameters here that you
	// would need for your own calculations.
	// These parameters are not standard in the original
	// version of DICE.
	
	// Allocate vectors
	dice->endog.ri_disc = new double[dice->config.nPeriods];		// Real interest rate (discounted) for present value calculations
	dice->endog.pv_damages = new double[dice->config.nPeriods];		// Present value of damages
	dice->endog.pv_abatecost = new double[dice->config.nPeriods];	// Present value of abatement costs
	dice->endog.totalcost = new double[dice->config.nPeriods];		// Total costs (abatement + damages)
	dice->endog.pv_totalcost = new double[dice->config.nPeriods];	// Present value of total costs (abatement + damages)
	return;
}

void populateDICE(DICE *dice, vector<double> parms)
{
	// Put dummy into place 0
	parms.insert(parms.begin(),-99);
	
		// Preferences ---------------------------------
	dice->config.elasmu =  (parms[1]);		// Elasticity of marginal utility of consumption
	dice->config.prstp =  (parms[2]);		// Initial rate of social time preference (per year)

	// Population and Technology -------------------
	dice->config.gama =  (parms[3]);		// Capital elasticity in production function
	dice->config.pop0 =  (parms[4]);		// Initial world population [Millions]
	dice->config.popadj =  (parms[5]);		// Growth rate to calibrate to 2050 population projection
	dice->config.popasym =  (parms[6]);	// Asymptotic world population [Millions]
	dice->config.dk =  (parms[7]);			// Depreciation rate on capital (per year)
	dice->config.q0 =  (parms[8]);			// Initial world gross output [Trillions 2005 US $]
	dice->config.k0 =  (parms[9]);			// Initial capital value [Trillions 2005 US $]
	dice->config.a0 =  (parms[10]);			// Initial level of total factor productivity (TFP)
	dice->config.ga0 =  (parms[11]);		// Initial growth rate for TFP (per 5 years)
	dice->config.dela =  (parms[12]);		// Decline rate of TFP (per 5 years)
	dice->config.optlrsav =  (parms[13]);	// Optimal long-run savings rate used for transversality
								

	// Emissions parameters ------------------------
	dice->config.gsigma1 =  (parms[14]);		// Initial growth of sigma (per year)
	dice->config.dsig =  (parms[15]);		// Decline rate of decarbonization (per period)
	dice->config.eland0 =  (parms[16]);		// Carbon emissions from land 2010 [GtCO2 per year]
	dice->config.deland =  (parms[17]);		// Decline rate of land emissions (per period)
	dice->config.e0 =  (parms[18]);			// Industrial emissions 2010 [GtCO2 per year]
	dice->config.miu0 =  (parms[19]);		// Initial emissions control rate for base case 2010
//	dice->config.sig0 = dice->config.e0 / (dice->config.q0 * (1 - dice->config.miu0));
								// Carbon Intensity 2010 [kgCO2 per output 2005 USD 2010]


	// Carbon cycle ---------------------------------
	// Initial conditions	
	dice->config.mat0 =  (parms[20]);		// Initial concentration in atmosphere 2010 [GtC]
	dice->config.mu0 =  (parms[21]);		// Initial concentration in upper strata [GtC]
	dice->config.ml0 =  (parms[22]);		// Initial concentration in lower strata [GtC]
	dice->config.mateq =  (parms[23]);		// Equilibrium concentration in atmosphere [GtC]
	dice->config.mueq =  (parms[24]);		// Equilibrium concentration in upper strata [GtC]
	dice->config.mleq =  (parms[25]);		// Equilibrium concentration in lower strata [GtC]

	// Flow parameters (Carbon cycle transition matricies)
	dice->config.b12 =  (parms[26]);
	dice->config.b23 =  (parms[27]);
	dice->config.b11 =  (parms[28]);
	dice->config.b21 =  (parms[29]);
	dice->config.b22 =  (parms[30]);
	dice->config.b32 =  (parms[31]);
	dice->config.b33 =  (parms[32]);


	// Climate model parameters ---------------------
	dice->config.t2xco2 =  (parms[33]);		// Equilibrium temperature impact [dC per doubling CO2]
	dice->config.fex0 =  (parms[34]);		// 2010 forcings of non-CO2 greenhouse gases (GHG) [Wm-2]
	dice->config.fex1 =  (parms[35]);		// 2100 forcings of non-CO2 GHG [Wm-2]
	dice->config.tocean0 =  (parms[36]);	// Initial lower stratum temperature change [dC from 1900]
	dice->config.tatm0 =  (parms[37]);		// Initial atmospheric temperature change [dC from 1900]
	dice->config.c10 =  (parms[38]);		// Initial climate equation coefficient for upper level
	dice->config.c1beta =  (parms[39]);	// Regression slope coefficient (SoA~Equil TSC)
	dice->config.c1 =  (parms[40]);			// Climate equation coefficient for upper level
	dice->config.c3 =  (parms[41]);			// Transfer coefficient upper to lower stratum
	dice->config.c4 =  (parms[42]);			// Transfer coefficient for lower level
	dice->config.fco22x =  (parms[43]);		// Forcings of equilibrium CO2 doubling [Wm-2]
	dice->config.lam =  (parms[44]);		// Climate model parameter
	

	// Climate damage parameters ---------------------
	dice->config.a10 =  (parms[45]);			// Initial damage intercept
	dice->config.a20 =  (parms[46]);		// Initial damage quadratic term
	dice->config.a1 =  (parms[47]);			// Damage intercept
	dice->config.a2 =  (parms[48]);		// Damage quadratic term
	dice->config.a3 =  (parms[49]);			// Damage exponent
	

	// Abatement cost --------------------------------
	dice->config.expcost2 =  (parms[50]);		// Exponent of control cost function
	dice->config.pback =  (parms[51]);		// Cost of backstop [2005$ per tCO2 2010]
	dice->config.gback =  (parms[52]);		// Initial cost decline backstop [cost per period]
	dice->config.limmiu =  (parms[53]);		// Upper limit on control rate after 2150
	dice->config.tnopol =  (parms[54]);		// Period before which no emissions controls base
	dice->config.cprice0 =  (parms[55]);		// Initial base carbon price [2005$ per tCO2]
	dice->config.gcprice =  (parms[56]);		// Growth rate of base carbon price (per year)
	

	// Participation parameters ----------------------	
	dice->config.periodfullpart =  (parms[57]);	// Period at which have full participation
	dice->config.partfract2010 =  (parms[58]);	// Fraction of emissions under control in 2010
	dice->config.partfractfull =  (parms[59]);	// Fraction of emissions under control at full time
	

	// Availability of fossil fuels ------------------
	dice->config.fosslim =  (parms[60]);	// Maximum cummulative extraction fossil fuels [GtC]
	
	// Scaling and inessential parameters ------------
	// "Note that these are unnecessary for the calculations but are for convenience"
	// Quoted directly from comments in original GAMS code
	dice->config.scale1 = 0.016408662;	// Multiplicitive scaling coefficient
	dice->config.scale2 = -3855.106895;// Additive scaling coefficient
	
	// Objective
	dice->endog.utility = 0.0;		// Welfare function (Sum of discounted utility of per capita consumption)
	
	// Initialize time series -------------------------
	for (int i=0; i<dice->config.nPeriods; i++)
	{
		dice->config.dateSeries[i] = dice->config.startYear + (dice->config.tstep * i);
		dice->config.l[i] = 0.0;
		dice->config.al[i] = 0.0;		
		dice->config.sigma[i] = 0.0;	 
		dice->config.rr[i] = 0.0;		
		dice->config.ga[i] = 0.0;		
		dice->config.forcoth[i] = 0.0;
		dice->config.gl[i] = 0.0;		
		dice->config.gcost[i] = 0.0;
		dice->config.gsig[i] = 0.0;		
		dice->config.etree[i] = 0.0;
		dice->config.cost1[i] = 0.0;
		dice->config.partfract[i] = 0.0;
		//dice->config.gfacpop[i] = 0.0;	// Appears in GAMS version, but is never used
		dice->config.pbacktime[i] = 0.0;
		dice->config.scc[i] = 0.0;
		dice->config.cpricebase[i] = 0.0;
		dice->config.photel[i] = 0.0;

		dice->endog.miu[i] = 0.0;
		dice->endog.forc[i] = 0.0;
		dice->endog.tatm[i] = 0.0;
		dice->endog.tocean[i] = 0.0;
		dice->endog.mat[i] = 0.0;
		dice->endog.mu[i] = 0.0;
		dice->endog.ml[i] = 0.0;
		dice->endog.e[i] = 0.0;
		dice->endog.eind[i] = 0.0;
		dice->endog.c[i] = 0.0;
		dice->endog.k[i] = 0.0;
		dice->endog.cpc[i] = 0.0;
		dice->endog.i[i] = 0.0;
		dice->endog.ri[i] = 0.0;
		dice->endog.y[i] = 0.0;
		dice->endog.ygross[i] = 0.0;
		dice->endog.ynet[i] = 0.0;
		dice->endog.damages[i] = 0.0;
		dice->endog.damfrac[i] = 0.0;
		dice->endog.abatecost[i] = 0.0;
		dice->endog.mcabate[i] = 0.0;
		dice->endog.cca[i] = 0.0;
		dice->endog.periodu[i] = 0.0;
		dice->endog.cprice[i] = 0.0;
		dice->endog.cemutotper[i] = 0.0;
	}

	for (int i=0; i<dice->config.nPeriods; i++)
	{
	  dice->endog.miu[i] =  (parms[i+61]);
	  dice->endog.s[i] =  (parms[i+121]);
	}
	
	// Initialize vectors
	for(int i=0; i<dice->config.nPeriods; i++) 
	{
		dice->endog.ri_disc[i] = 0.0;
		dice->endog.pv_damages[i] = 0.0;
		dice->endog.pv_abatecost[i] = 0.0;
		dice->endog.totalcost[i] = 0.0;
		dice->endog.pv_totalcost[i] = 0.0;
	}
	
	// Calculate values for the exogenous variables -------------------------
	// Information from the exogenous variables is used
	// to help define some of the bounds initialized later
	// in this function.
	calcExog(dice);
	
		// Numerical bounds on values -------------------------------------------
	// Scalars
	dice->config.k_lo = 1.0;
	dice->config.mat_lo = 10.0;
	dice->config.mu_lo = 100.0;
	dice->config.ml_lo = 1000.0;
	dice->config.c_lo = 2.0;
	dice->config.tocean_up = 20.0;
	dice->config.tocean_lo = -1.0;
	dice->config.tatm_lo = 0.0;
	dice->config.tatm_up = 40.0;
	dice->config.cpc_lo = 0.01;
	dice->config.y_lo = 0.0;
	dice->config.ygross_lo = 0.0;
	dice->config.i_lo = 0.0;
	dice->config.cca_up = dice->config.fosslim;
	
	// Time series
	for(int i=0; i<dice->config.nPeriods; i++)
	{
		// Control rate limit
		if (i < 30) {
			dice->config.miu_up[i] = 1.0;
		}
		else	{
			dice->config.miu_up[i] = dice->config.limmiu * dice->config.partfract[i];
		}
		
	}
	
	
	// Timesteps at which bounds are exceeded ----------------------------
	dice->endog.k_lo_step = 0;
	dice->endog.mat_lo_step = 0;
	dice->endog.mu_lo_step = 0;
	dice->endog.ml_lo_step = 0;
	dice->endog.c_lo_step = 0;
	dice->endog.tocean_up_step = 0;
	dice->endog.tocean_lo_step = 0;
	dice->endog.tatm_lo_step = 0;
	dice->endog.tatm_up_step = 0;
	dice->endog.cpc_lo_step = 0;
	dice->endog.y_lo_step = 0;
	dice->endog.ygross_lo_step = 0;
	dice->endog.i_lo_step = 0;
	dice->endog.cca_up_step = 0;
	dice->endog.miu_up_step = 0;
	
	return;
}