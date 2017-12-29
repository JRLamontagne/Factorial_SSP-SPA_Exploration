# -*- coding: utf-8 -*-
"""
Created on Sun Jun 26 22:13:04 2016

@author: jrl276
"""

from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection
import matplotlib.cm as cm
import matplotlib as mpl
import numpy as np

SPA_LUC_4=[0.00,0.00,0.00,0.00,0.25,0.50,0.25,0.50,0.25,0.00,0.25,0.25,0.25,0.50,0.25,0.25,0.50,0.00,0.00,0.50,0.25,0.25,0.00,0.25,0.25,0.25,0.25,0.00,0.50,0.00,0.50,0.50]
filename = "SPA4.svg"
data = list(SPA_LUC_4)

for i in range(32):
    data[i] = data[i]*100

norm = mpl.colors.Normalize(vmin=0, vmax=50)
cmap = cm.coolwarm
cmap = cm.Oranges
colors=cm.ScalarMappable(norm=norm, cmap=cmap)
colors.set_array(data)
a = colors.to_rgba(data)

fig = plt.figure(figsize=(12,5))
ax = fig.add_subplot(111)

m = Basemap(projection='robin', lon_0=0,resolution='c',)

m.drawmapboundary(fill_color='white', zorder=-1)
m.drawparallels(np.arange(-90.,91.,30.), labels=[1,0,0,1], dashes=[10000,1], linewidth=0.25, color=[0.5,0.5,0.5,0.35],fontsize=14)
m.drawmeridians(np.arange(0., 360., 60.), labels=[1,0,0,1], dashes=[10000,1], linewidth=0.25, color=[0.5,0.5,0.5,0.35],fontsize=14)

GCAM_32 = ['PRI','USA','VIR']
GCAM_1 = ['BDI','COM','DJI','ERI','ETH','KEN','MDG','MUS','REU','RWA','SDS','SDN','SOM','UGA','SOL']
GCAM_2 = ['DZA','EGY','ESH','LBY','MAR','TUN','SAH']
GCAM_3 = ['AGO','BWA','LSO','MOZ','MWI','NAM','SWZ','TZA','ZMB','ZWE']
GCAM_4 = ['BEN','BFA','CAF','CIV','CMR','COD','COG','CPV','GAB','GHA','GIN','GMB','GNB','GNQ','LBR','MLI','MRT','NER','NGA','SEN','SLE','STP','TCD','TGO']
GCAM_6 = ['AUS','NZL']
GCAM_7 = ['BRA']
GCAM_8 = ['CAN']
GCAM_9 = ['ABW','AIA','ANT','ATG','BHS','BLZ','BMU','BRB','CRI','CUB','CYM','DMA','DOM','GLP','GRD','GTM','HND','HTI','JAM','KNA','LCA','MSR','MTQ','NIC','PAN','SLV','TTO','VCT']
GCAM_10 = ['ARM','AZE','GEO','KAZ','KGZ','MNG','TJK','TKM','UZB']
GCAM_11 = ['CHN','HKG','MAC']
GCAM_13 = ['BGR','CYP','CZE','EST','HUN','LTU','LVA','MLT','POL','ROU','SVK','SVN']
GCAM_14 = ['AND','AUT','BEL','CHI','DEU','DNK','ESP','FIN','FLK','FRA','FRO','GBR','GIB','GRC','GRL','IMN','IRL','ITA','LUX','MCO','NLD','PRT','SHN','SMR','SPM','SWE','TCA','VAT','VGB','WLF']
GCAM_15 = ['BLR','MDA','UKR']
GCAM_16 = ['ALB','BIH','HRV','MKD','MNE','SCG','SRB','TUR','YUG']
GCAM_17 = ['CHE','ISL','LIE','NOR','SJM'] #hre
GCAM_18 = ['IND']
GCAM_19 = ['IDN']
GCAM_20 = ['JPN']
GCAM_21 = ['MEX']
GCAM_22 = ['ARE','BHR','IRN','IRQ','ISR','JOR','KWT','LBN','OMN','PSE','QAT','SAU','SYR','YEM']
GCAM_23 = ['PAK']
GCAM_24 = ['RUS']
GCAM_25 = ['ZAF']
GCAM_26 = ['GUF','GUY','SUR','VEN']
GCAM_27 = ['BOL','CHL','ECU','PER','PRY','URY']
GCAM_28 = ['AFG','ASM','BGD','BTN','LAO','LKA','MDV','NPL']
GCAM_29 = ['KOR']
GCAM_30 = ['BRN','CCK','COK','CXR','FJI','FSM','GUM','KHM','KIR','MHL','MMR','MNP','MYS','MYT','NCL','NFK','NIU','NRU','PCI','PCN','PHL','PLW','PNG','PRK','PYF','SGP','SLB','SYC','THA','TKL','TLS','TON','TUV','VNM','VUT','WSM']
GCAM_31 = ['TWN']
GCAM_5 = ['ARG']
GCAM_12 = ['COL']
    
list_list = [GCAM_1,GCAM_2,GCAM_3,GCAM_4,GCAM_5,GCAM_6,GCAM_7,GCAM_8,GCAM_9,GCAM_10,GCAM_11,GCAM_12,GCAM_13,GCAM_14,GCAM_15,GCAM_16,GCAM_17,GCAM_18,GCAM_19,GCAM_20,GCAM_21,GCAM_22,GCAM_23,GCAM_24,GCAM_25,GCAM_26,GCAM_27,GCAM_28,GCAM_29,GCAM_30,GCAM_31,GCAM_32]
m.readshapefile('../data/ne_110m_admin_0_countries_lakes/ne_110m_admin_0_countries_lakes','comarques')
num = len(list_list)
patches2 = []
for info, shape in zip(m.comarques_info,m.comarques):
    for i in range(num):
        if info['adm0_a3'] in list_list[i]:
            patches1 = []
            patches1.append( Polygon(np.array(shape), True) )
            ax.add_collection(PatchCollection(patches1,facecolor=a[i,:],edgecolor='k',linewidths=1.,zorder=2))
            
ax.set_title('SPA2 LUC Tax Fraction',fontsize=25,y=1.0)
plt.annotate(2100,xy=(0.05,0.35),xytext=(0.05,0.35),xycoords='axes fraction',fontsize=30)
cb = m.colorbar(colors,'right')
cb.ax.tick_params(labelsize=14)
cb.set_label(r'Fraction of CO$_{2}$ Tax (%)',fontsize=16,rotation=270,labelpad=20)

plt.show()
fig.savefig(filename,format='svg')