/* Copyright (C) 2013 Gregory Garner, Klaus Keller, Patrick Reed, Martha Butler, and others

  CDICE is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.
 
  CDICE is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.
 
  You should have received a copy of the GNU Lesser General Public License
  along with the CDICE code.  If not, see <http://www.gnu.org/licenses/>.
 */

//#ifdef CDICEMOD

#include "CDICE.h"

extern DICE dice;
extern DICE* dicePtr;


//============================================================================
// calcExog(DICE *dice)
// 
// Calculate exogenous time series in the Config section of the dice structure
//
// Return ()
// - 'dice' structure config time series are updated
//============================================================================
void calcExog(DICE *dice)
{
	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;   //need this to propagate savings rate
	int tlim = config->nPeriods;

	//cout << "calcExog: beginning " << endl;
	
	
	// Initial timestep calculations and settings ----------------------------
	config->l[0] = config->pop0;			// Population
	config->ga[0] = config->ga0;			// Growth rate for TFP
	config->al[0] = config->a0;			// Level of TFP
	config->gsig[0] = config->gsigma1;		// Change in sigma (cumulative improvement in energy efficiency)
	config->sigma[0] = config->sig0;		// CO2-equivalent-emissions output ratio
	config->pbacktime[0] = config->pback;	// Cost of backstop
	config->cost1[0] = config->pbacktime[0]*config->sigma[0]/config->expcost2/1000;
									// Adjusted cost for backstop
	config->etree[0] = config->eland0;		// Emissions from deforestation
	config->rr[0] = 1;					// Average utility social discount rate
	config->forcoth[0] = config->fex0;		// Forcing from other GHG
	config->partfract[0] = config->partfract2010;
									// Fraction of emissions under control regime
	config->cpricebase[0] = config->cprice0;// Carbon price in base case
	config->sig0 = config->e0 / (config->q0 * (1 - config->miu0));
									// Carbon Intensity 2010 [kgCO2 per output 2005 USD 2010]
	
	
	// Iterate over the full time series
	for (int t=1; t<tlim; t++)
	{
		// Population
		config->l[t] = config->l[t-1]*(pow(config->popasym/config->l[t-1], config->popadj));
	
		// Growth rate for TFP
		config->ga[t] = config->ga0*exp(-1*config->dela*config->tstep*double(t));
	
		// Level for TFP
		config->al[t] = config->al[t-1]/(1-config->ga[t-1]);
		
		// Change in sigma (cumulative improvement in energy efficiency)
		config->gsig[t] = config->gsig[t-1]*(pow(1+config->dsig, config->tstep));
		
		// CO2-equivalent-emissions output ratio
		config->sigma[t] = config->sigma[t-1]*exp(config->gsig[t-1]*config->tstep);
		
		// Cost of backstop
		config->pbacktime[t] = config->pback*pow(1-config->gback, double(t));
		
		// Adjusted cost for backstop
		config->cost1[t] = config->pbacktime[t]*config->sigma[t]/config->expcost2/1000;
		
		// Emissions from deforestation
		config->etree[t] = config->eland0*pow(1-config->deland, double(t));
		
		// Average utility social discount rate	
		config->rr[t] = 1/pow(1+config->prstp, config->tstep*double(t));
		
		// Forcings from other GHG
		if (t < 19) {
			config->forcoth[t] = config->fex0+(1.0/18.0)*(config->fex1-config->fex0)*double(t);
		}
		else {
			config->forcoth[t] = config->fex0+(config->fex1-config->fex0);
		}
		
		// Fraction of emissions under control regime
		if (t > config->periodfullpart) {
			config->partfract[t] = config->partfractfull;
		}
		else {
			config->partfract[t] = config->partfract2010+(config->partfractfull-config->partfract2010)*(double(t)/config->periodfullpart);
		}
		
		// Carbon price in base case
		config->cpricebase[t] = config->cprice0*pow(1+config->gcprice, config->tstep*double(t));
		
	}
  
  
	// Transient TSC Correction ("Speed of Adjustment Parameter")
	config->c1 = config->c10+config->c1beta*(config->t2xco2-2.9);


	return;
}

//=============================================================================
// calcClim1(DICE *dice)
//
// Calculate the first time step of the climate-related endog variables
//
// Return ()
// - 'dice' endog structure variables are updated
//=============================================================================
void calcClim1(DICE *dice)
{

	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;
	
	// Carbon pools
	endog->mat[0] = config->mat0;
	if(dice->endog.mat[0] < dice->config.mat_lo) {
		dice->endog.mat[0] = dice->config.mat_lo;
		dice->endog.mat_lo_step = 0;
	}

	endog->mu[0] = config->mu0;
	if(dice->endog.mu[0] < dice->config.mu_lo) {
		dice->endog.mu[0] = dice->config.mu_lo;
		dice->endog.mu_lo_step = 0;
	}

	endog->ml[0] = config->ml0;
	if(dice->endog.ml[0] < dice->config.ml_lo) {
		dice->endog.ml[0] = dice->config.ml_lo;
		dice->endog.ml_lo_step = 0;
	}
	
	// Atmospheric temperature
	endog->tatm[0] = config->tatm0;
	if(dice->endog.tatm[0] < dice->config.tatm_lo) {
		dice->endog.tatm[0] = dice->config.tatm_lo;
		dice->endog.tatm_lo_step = 0;
	}
	if(dice->endog.tatm[0] > dice->config.tatm_up) {
		dice->endog.tatm[0] = dice->config.tatm_up;
		dice->endog.tatm_up_step = 0;
	}
	
	// Oceanic temperature
	endog->tocean[0] = config->tocean0;
	if(dice->endog.tocean[0] > dice->config.tocean_up) {
		dice->endog.tocean[0] = dice->config.tocean_up;
		dice->endog.tocean_up_step = 0;
	}
	if(dice->endog.tocean[0] < dice->config.tocean_lo) {
		dice->endog.tocean[0] = dice->config.tocean_lo;
		dice->endog.tocean_lo_step = 0;
	}
	
	// Radiative forcing
	endog->forc[0] = config->fco22x*(log(endog->mat[0]/588.000)/log(2.0))+config->forcoth[0];

	return;
}

//=============================================================================
//	calcEcon1(DICE *dice)
//
// Calculate the first time step for the economic variables
//
// Return ()
// - 'dice' endog structure variables updated
//=============================================================================
void calcEcon1(DICE *dice)
{

	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;

	//char dummychar;
	//cout << "calcEcon1: beginning first time step\n";
	
	// Marginal cost of abatement
	endog->mcabate[0] = config->pbacktime[0]*pow(endog->miu[0],(config->expcost2-1));
		
	// Damages fraction
	endog->damfrac[0] = config->a1*endog->tatm[0]+config->a2*pow(endog->tatm[0],config->a3);

	// Capital stock
	endog->k[0] = config->k0;
	if(dice->endog.k[0] < dice->config.k_lo) {
		dice->endog.k[0] = dice->config.k_lo;
		dice->endog.k_lo_step = 0;
	}
	
	// Carbon price
	endog->cprice[0] = config->pbacktime[0]*pow((endog->miu[0]/config->partfract[0]),(config->expcost2-1));
	
	// Gross world product (gross abatement and damages)
	endog->ygross[0] = config->al[0]*pow((config->l[0]/1000.0),(1.0-config->gama))*pow(endog->k[0],config->gama);
	if(dice->endog.ygross[0] < dice->config.ygross_lo) {
		dice->endog.ygross[0] = dice->config.ygross_lo;
		dice->endog.ygross_lo_step = 0;
	}

	// Net output damages
	endog->ynet[0] = endog->ygross[0]*(1.0-endog->damfrac[0]);
	
	// Abatement costs
	endog->abatecost[0] = endog->ygross[0]*config->cost1[0]*pow(endog->miu[0],config->expcost2)*pow(config->partfract[0],(1-config->expcost2));

	// Damages
	endog->damages[0] = endog->ygross[0]*endog->damfrac[0];
	
	// Industrial emissions
	endog->eind[0] = config->sigma[0]*endog->ygross[0]*(1.0-endog->miu[0]);

	// Total emissions	
	endog->e[0] = endog->eind[0]+config->etree[0];

	// Cumulative emissions
	endog->cca[0] = 90.0;
	if(dice->endog.cca[0] > dice->config.cca_up) {
		dice->endog.cca[0] = dice->config.cca_up;
		dice->endog.cca_up_step = 0;
	}
	
	// Gross world product (net of abatement and damages)
	endog->y[0] = endog->ynet[0]-endog->abatecost[0];
	if(dice->endog.y[0] < dice->config.y_lo) {
		dice->endog.y[0] = dice->config.y_lo;
		dice->endog.y_lo_step = 0;
	}
	
	// Investment
	endog->i[0] = endog->s[0]*endog->y[0];
	if(dice->endog.i[0] < dice->config.i_lo) {
		dice->endog.i[0] = dice->config.i_lo;
		dice->endog.i_lo_step = 0;
	}

	// Consumption
	endog->c[0] = endog->y[0]-endog->i[0];
	if(dice->endog.c[0] < dice->config.c_lo) {
		dice->endog.c[0] = dice->config.c_lo;
		dice->endog.c_lo_step = 0;
	}
	
	// Per capita consumption
	endog->cpc[0] = 1000.0*endog->c[0]/config->l[0];
	if(dice->endog.cpc[0] < dice->config.cpc_lo) {
		dice->endog.cpc[0] = dice->config.cpc_lo;
		dice->endog.cpc_lo_step = 0;
	}
	
	return;
}


//=============================================================================
// calcClim(DICE *dice, int t)
//
// Calculate the climate model component for time step 't'
//
// Return()
// - 'dice' endogenous structure variables updated
//=============================================================================
void calcClim(DICE *dice, int t)
{

	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;
	
	// Carbon pools (carbon cycle box model)
	endog->mat[t] = (endog->e[t-1]*(5.0/3.666))+config->b11*endog->mat[t-1]+config->b21*endog->mu[t-1];
	if(dice->endog.mat[t] < dice->config.mat_lo) {
		dice->endog.mat[t] = dice->config.mat_lo;
		dice->endog.mat_lo_step = t;
	}

	endog->mu[t] = config->b12*endog->mat[t-1]+config->b22*endog->mu[t-1]+config->b32*endog->ml[t-1];
	if(dice->endog.mu[t] < dice->config.mu_lo) {
		dice->endog.mu[t] = dice->config.mu_lo;
		dice->endog.mu_lo_step = t;
	}

	endog->ml[t] = config->b33*endog->ml[t-1]+config->b23*endog->mu[t-1];
	if(dice->endog.ml[t] < dice->config.ml_lo) {
		dice->endog.ml[t] = dice->config.ml_lo;
		dice->endog.ml_lo_step = t;
	}

	// Radiatice forcing
	endog->forc[t] = config->fco22x*(log(endog->mat[t]/588.000)/log(2.0))+config->forcoth[t];
						
	// Atmospheric temperature
	endog->tatm[t] = endog->tatm[t-1]+config->c1*((endog->forc[t]-((config->fco22x/config->t2xco2)*endog->tatm[t-1]))-(config->c3*(endog->tatm[t-1]-endog->tocean[t-1])));
	if(dice->endog.tatm[t] < dice->config.tatm_lo) {
		dice->endog.tatm[t] = dice->config.tatm_lo;
		dice->endog.tatm_lo_step = t;
	}
	if(dice->endog.tatm[t] > dice->config.tatm_up) {
		dice->endog.tatm[t] = dice->config.tatm_up;
		dice->endog.tatm_up_step = t;
	}

	// Oceanic temperature
	endog->tocean[t] = endog->tocean[t-1]+config->c4*(endog->tatm[t-1]-endog->tocean[t-1]);
	if(dice->endog.tocean[t] > dice->config.tocean_up) {
		dice->endog.tocean[t] = dice->config.tocean_up;
		dice->endog.tocean_up_step = t;
	}
	if(dice->endog.tocean[t] < dice->config.tocean_lo) {
		dice->endog.tocean[t] = dice->config.tocean_lo;
		dice->endog.tocean_lo_step = t;
	}

	return;
}

//=============================================================================
// calcEcon(DICE *dice, int t)
//
// Calculate the economic model component for the time step 't'.
//
// Return()
// - 'dice' endogenous structure variables updated
//=============================================================================
void calcEcon(DICE *dice, int t)
{

	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;
	

	// Marginal cost of abatement
	endog->mcabate[t] = config->pbacktime[t]*pow(endog->miu[t],(config->expcost2-1));
		
	// Damages fraction
	endog->damfrac[t] = config->a1*endog->tatm[t]+config->a2*pow(endog->tatm[t],config->a3);

	// Capital stock
	endog->k[t] = pow((1-config->dk),config->tstep)*endog->k[t-1]+config->tstep*endog->i[t-1];
	if(dice->endog.k[t] < dice->config.k_lo) {
		dice->endog.k[t] = dice->config.k_lo;
		dice->endog.k_lo_step = t;
	}
	
	// Carbon price
	endog->cprice[t] = config->pbacktime[t]*pow((endog->miu[t]/config->partfract[t]),(config->expcost2-1));
	
	// Gross world product (gross abatement and damages)
	endog->ygross[t] = config->al[t]*pow((config->l[t]/1000.0),(1.0-config->gama))*pow(endog->k[t],config->gama);
	if(dice->endog.ygross[t] < dice->config.ygross_lo) {
		dice->endog.ygross[t] = dice->config.ygross_lo;
		dice->endog.ygross_lo_step = t;
	}

	// Net output damages
	endog->ynet[t] = endog->ygross[t]*(1.0-endog->damfrac[t]);
	
	// Abatement costs
	endog->abatecost[t] = endog->ygross[t]*config->cost1[t]*pow(endog->miu[t],config->expcost2)*pow(config->partfract[t],(1-config->expcost2));

	// Damages
	endog->damages[t] = endog->ygross[t]*endog->damfrac[t];
	
	// Industrial emissions
	endog->eind[t] = config->sigma[t]*endog->ygross[t]*(1.0-endog->miu[t]);

	// Total emissions	
	endog->e[t] = endog->eind[t]+config->etree[t];

	// Cumulative emissions
	endog->cca[t] = endog->cca[t-1]+endog->eind[t-1]*5.0/3.666;
	if(dice->endog.cca[t] > dice->config.cca_up) {
		dice->endog.cca[t] = dice->config.cca_up;
		dice->endog.cca_up_step = t;
	}
	
	// Gross world product (net of abatement and damages)
	endog->y[t] = endog->ynet[t]-endog->abatecost[t];
	if(dice->endog.y[t] < dice->config.y_lo) {
		dice->endog.y[t] = dice->config.y_lo;
		dice->endog.y_lo_step = t;
	}
	
	// Investment
	endog->i[t] = endog->s[t]*endog->y[t];
	if(dice->endog.i[t] < dice->config.i_lo) {
		dice->endog.i[t] = dice->config.i_lo;
		dice->endog.i_lo_step = t;
	}

	// Consumption
	endog->c[t] = endog->y[t]-endog->i[t];
	if(dice->endog.c[t] < dice->config.c_lo) {
		dice->endog.c[t] = dice->config.c_lo;
		dice->endog.c_lo_step = t;
	}
	
	// Per capita consumption
	endog->cpc[t] = 1000.0*endog->c[t]/config->l[t];
	if(dice->endog.cpc[t] < dice->config.cpc_lo) {
		dice->endog.cpc[t] = dice->config.cpc_lo;
		dice->endog.cpc_lo_step = t;
	}
	
	// Real interest rate
	endog->ri[t-1] = (1.0+config->prstp)*pow((endog->cpc[t]/endog->cpc[t-1]),(config->elasmu/config->tstep))-1.0;

	return;
}


//=============================================================================
// postProcess(DICE *dice)
//
// Calculate objective function and any additional quantities added by the user
//
// Return()
// - 'dice' endogenous structure variables are updated
//=============================================================================
void postProcess(DICE *dice)
{

	Config *config = &dice->config;
	Endog  *endog  = &dice->endog;


	// Calculate additional model outputs ------------------------------------------
	for (int t=0; t<config->nPeriods; t++)
	{

		// One period utility function
		endog->periodu[t] = (pow((endog->c[t]*1000.0/config->l[t]),(1.0-config->elasmu))-1.0)/(1.0-config->elasmu)-1.0;
		
		// Period utility
		endog->cemutotper[t] = endog->periodu[t]*config->l[t]*config->rr[t];
		
		// Total cost of abatement and damages
		endog->totalcost[t] = endog->damages[t] + endog->abatecost[t];
	
	}


	// Discounted utility of consumption (objective function) -----------------------
	double tempsum;
	tempsum = 0.0;
	
	for (int t=0; t<config->nPeriods; t++)
	{
		tempsum += endog->cemutotper[t];
	}

	endog->utility = (config->tstep*config->scale1*tempsum)+config->scale2;
	

	// Present Value Calculations for damages and abatement costs
	endog->pv_damages[0] = endog->damages[0];
	endog->pv_abatecost[0] = endog->abatecost[0];
	endog->pv_totalcost[0] = endog->totalcost[0];

	for (int t=1; t<config->nPeriods; t++)
	{
		if(endog->ri[t] <= 0.0) {
			endog->ri_disc[t] = 0.0;
		}
		else {
			endog->ri_disc[t] = 1.0/pow(1.0 + endog->ri[t],config->tstep*double(t));
		}
		
		endog->pv_damages[t] = endog->pv_damages[t-1]+endog->ri_disc[t]*endog->damages[t];
		endog->pv_abatecost[t] = endog->pv_abatecost[t-1]+endog->ri_disc[t]*endog->abatecost[t];
		endog->pv_totalcost[t] = endog->pv_totalcost[t-1]+endog->ri_disc[t]*endog->totalcost[t];
	}
	
	return;
}
	

//=============================================================================
// processModel(DICE *dice)
//
// Perform a full iteration of the model
// - calculate the exogenous time series
// - do time step 1 of both climate and econ model components
// - loop the remaining time steps (climate and econ)
// - calculate the objective function and other model results
//
// Return()
// - Full 'dice' structure is calculated.
//=============================================================================
void processModel(DICE *dice)
{

	//char dummychar;
	//cout << "processModel: calling calcExog\n";
	//cin >> dummychar;
	
	// Calculate exogenous time series
	calcExog(dice);
	
	//cout << "processModel: calling calcClim1\n";
	//cin >> dummychar;

	// Calculate the first time step of climate model
	calcClim1(dice);
	
	//cout << "processModel: calling calcEcon1\n";
	//cin >> dummychar;

	// Calculate the first time step of economic model
	calcEcon1(dice);

	//cout << "processModel: stepping through the decades\n";
	//cin >> dummychar;
	
	// Calculate the rest of the time series
	for (int tIndex=1; tIndex<dice->config.nPeriods; tIndex++)
	{
		calcClim(dice, tIndex);
		calcEcon(dice, tIndex);
	}
	
	//do the postprocessing

	//cout << "processModel: calling postProcess\n";
	//cin >> dummychar;
	
	postProcess(dice);
	
	
	return;
}


//#endif    //CDICEMOD

