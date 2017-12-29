# Factorial Exploration of the SSP-SPA Assumptions
Large scale factorial exploration of the Shared Socioeconomic Pathways (SSPs) and Shared Policy Assumptions (SPAs) using the Globl Change Assessment Model [GCAM](https://github.com/JGCRI/gcam-core).  This repository includes the results of approximately 33,000 global change scenarios generated by sampling the elements of [Scenario Matrix Framework](https://link.springer.com/article/10.1007/s10584-013-0906-1) as quantified by [Calvin et al. (2017)](https://www.sciencedirect.com/science/article/pii/S095937801630084X) and evaluated using GCAM. The repository also includes figure generation scripts for the experiment reported in Lamontagne et al. (2018).

Each row of the data.csv file in the [data directory](https://github.com/JRLamontagne/Factorial_SSP-SPA_Exploration/tree/master/data) corresponds to a single Global Change Scenario.  The first nine columns contain categorical variables corresponding to GCAM input sampling levels from the factorial sampling space detaied in Lamontagne et al. (2018). The Pop/GDP, Ind/Train/Build, AGLU, and Fossil sampling dimensions (columns 1-4) have SSP specific sampling levels (0-SSP1, 1-SSP2, 2-SSP3, 3-SSP4, 4-SSP5).  The Energy sampling dimension (column 5) has three sampling levels (0-Low, 1-Mid, 2-High). The CCS sampling dimension (column 6) has two sampling levels (0-Low, 1-High). Columns 7-9 correspond to elements of the carbon price regime (see Figure 2 in Lamontagne et al. (2018). The long-term carbon price (column 7) has three sampling levels (0-Low Price, 1-High Price, 2-No Price), the LUC emissions price (column 8) has three sampling levels (0-Low Price Fragmentation, 1-High Price Fragmentation, 2-No Price), and the short term price fragmentation (column 9) has three sampling levels (0-Low Price Fragmentation, 1-High Price Fragmentation, No Price). The exact numerical meaning of each sampling level is provided by [Calvin et al. (2017)](https://www.sciencedirect.com/science/article/pii/S095937801630084X). The 10th and 11th columns correspond to the average cost of the abatement policy and 2100 forcing level respectively.  The parallel axes plots used by Lamontagne et al. (2018) to visualize the experimental space can be replicated using the [D3](https://d3js.org/) parallel axes [tool](https://reed.cee.cornell.edu/parallel-axis-categories/parallel/) developed and hosted by the [Reed Group at Cornell University](https://reed.cee.cornell.edu/index.php/Main_Page).

Each row of the SSP-SPA-CF.csv file in the [data directory](https://github.com/JRLamontagne/Factorial_SSP-SPA_Exploration/tree/master/data) corresponds to a SSP-SPA-RCP combination, wherein a SSP-SPA quantification from [Calvin et al. (2017)](https://www.sciencedirect.com/science/article/pii/S095937801630084X) is implemented using GCAM's target finding routine to achieve aneither 4.5 or 6.0 W/m^2 climate forcing in 2100.

Figure_3.m in the [figure script directory](https://github.com/JRLamontagne/Factorial_SSP-SPA_Exploration/tree/master/figure_script) generates a scatter plot of forcing vs. cost for the sampled scenarios detailed in data.csv out by tax policy, with climate forcing 4.5 and 6.0 highlighted, and the cannoncial SSP-SPA combinations from [Calvin et al. (2017)](https://www.sciencedirect.com/science/article/pii/S095937801630084X) plotted.

plot_GCAM_ag.py in the [figure script directory](https://github.com/JRLamontagne/Factorial_SSP-SPA_Exploration/tree/master/figure_script) provides an example producing global plots of GCAM region/aez data, including agricultural yields (see Lamontagne et al. (2018) Figures 5B and 11A). plot_GCAM_regions.py in the in the [figure script directory] provides an example producing global plots of GCAM regions' data (see Lamontagne et al. (2018) Figures 5A, 7A, 7B, and 10ABC).

**Requirements:**
[Matlab](https://www.mathworks.com/products/matlab.html), [Matplotlib](http://matplotlib.org/) including [Basemap](https://matplotlib.org/basemap/), [Numpy](http://www.numpy.org/), [geojson](https://pypi.python.org/pypi/geojson), and [descartes](https://pypi.python.org/pypi/descartes).  Python scripts have only been tested on Python 2.7.  Still in active development.

**Citation:**
```
Lamontagne, J.R., P.M. Reed, R. Link, K.V. Calvin, L.E. Clarke, and J.A. Edmonds. Large Ensemble Analytic 
Framework for Consequence Driven Discovery of Climate Change Scenarios, Earth's Future, (in Revision), 2018.
```
### License
Copyright (C) 2017 Jon Lamontagne. Released under the [MIT liscense](LICENSE.md).
