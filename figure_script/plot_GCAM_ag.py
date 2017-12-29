# -*- coding: utf-8 -*-
"""
Created on Wed Nov 09 13:06:12 2016

@author: jrl276
"""

import geojson
from descartes import PolygonPatch
import matplotlib.pyplot as plt
from mpl_toolkits.basemap import Basemap
import matplotlib.cm as cm
import matplotlib as mpl
import numpy as np

#Define GCAM regions
region = {'Russian Fed':24,'Canada':8,'Usa':32,'Norway':17,'Finland':14,'Sweden':14,'Iceland':17,'Estonia':13,'Uk':14,'Latvia':13,'Denmark':14,'Kazakhstan':10,'Lithuania':13,'Ireland':14,'Germany':14,'Belarus':15,'Netherlands':14,'China':11,'Bel-lux':14,'Mongolia':10,'France':14,'Slovakia':13,'Poland':13,'Czech Rep':13,'Ukraine':15,'Austria':14,'Moldova Rep':15,'Hungary':13,'Romania':13,'Italy':14,'Switzerland':17,'Slovenia':13,'Croatia':16,'Bosnia Herzg':16,'Yugoslav Fr':16,'Japan':20,'Spain':14,'Georgia':10,'Andorra':14,'Bulgaria':13,'Kyrgyzstan':10,'Portugal':14,'Macedonia':16,'Turkey':16,'Azerbaijan':10,'Turkmenistan':10,'Uzbekistan':10,'North Korea':30,'Albania':16,'Greece':14,'Armenia':10,'Tajikistan':10,'Iran':22,'Afghanistan':28,'Syria':22,'Iraq':22,'Algeria':2,'Tunisia':2,'Pakistan':23,'South Korea':29,'Morocco':2,'Egypt':2,'Lybia':2,'Lebanon':22,'India':18,'Libya':2,'Israel':22,'Mexico':21,'Jordan':22,'Nepal':28,'Kuwait':22,'Saudi Arabia':22,'Myanmar':30,'Bhutan':28,'Western Sahara':2,'Bangladesh':28,'Mauritania':4,'Qatar':22,'Untd Arab Em':22,'Mali':4,'Cuba':9,'Laos':28,'Hong Kong':11,'Viet Nam':30,'Australia':6,'Niger':4,'Haiti':9,'Dominican Rp':9,'Chad':4,'Sudan':1,'Oman':22,'Thailand':30,'Philippines':30,'Belize':9,'Senegal':4,'Guatemala':9,'Honduras':9,'Burkina Faso':4,'Brazil':7,'New Zealand':6,'Eritrea':1,'El Salvador':9,'Panama':9,'Ethiopia':1,'Kenya':1,'Gambia':4,'Nigeria':4,'Liberia':4,'Cambodia':30,'Guineabissau':4,'Yemen':22,'Guinea':4,'Cameroon':4,'Nicaragua':9,'Colombia':12,'Venezuela':26,'Suriname':26,'Djibouti':1,'Somalia':1,'Costa Rica':9,'Aruba':9,'Trinidad Tob':9,'Ghana':4,'Togo':4,'Benin':4,'Cent Afr Rep':4,'Cote Divoire':4,'Sri Lanka':28,'Sierra Leone':4,'Zaire':4,'Brunei Darsm':30,'Guyana':26,'Uganda':1,'Fr Guiana':26,'Eq Guinea':4,'Indonesia':19,'Malaysia':30,'Singapore':30,'Ecuador':27,'Rwanda':1,'Tanzania':3,'Gabon':4,'Congo':4,'Burundi':1,'Peru':27,'Bolivia':27,'Chile':27,'Angola':3,'Papua N Guin':30,'Zambia':3,'Malawi':3,'Mozambique':3,'Namibia':3,'Madagascar':1,'Zimbabwe':3,'Lesotho':3,'Botswana':3,'Swaziland':3,'Paraguay':27,'Uruguay':27,'Argentina':5,'South Africa':25}

#Load in Data
l = np.loadtxt('../data/SSP1_Yield_Improve.txt')

#Define Colormap
norm = mpl.colors.Normalize(vmin=-115, vmax=190)
cmap = cm.RdYlGn
colors=cm.ScalarMappable(norm=norm, cmap=cmap)
colors.set_array(l)
a = colors.to_rgba(l)
a = np.reshape(a,[32,18,4])

#Load in geojson file
with open("../data/aez-w-greenland.geojson") as json_file:
    json_data = geojson.load(json_file)


#Create Figure
plt.clf()
fig = plt.figure(figsize=(10,5))
ax = fig.add_subplot(111)

#Set basemap
m = Basemap(projection='robin', lon_0=0,resolution='c')
m.drawmapboundary(fill_color='white', zorder=-1)
m.drawparallels(np.arange(-90.,91.,30.), labels=[1,0,0,1], dashes=[1,1], linewidth=0.25, color=[0.5,0.5,0.5,0.35],fontsize=14)
m.drawmeridians(np.arange(0., 360., 60.), labels=[1,0,0,1], dashes=[1,1], linewidth=0.25, color=[0.5,0.5,0.5,0.35],fontsize=14)
m.drawcoastlines(color='0.6', linewidth=1)

#Color GCAM AEZ regions
for i in range(2799):
    coordlist = json_data.features[i]['geometry']['coordinates'][0]
    if i < 2796:
        name = json_data.features[i]['properties']['CTRYNAME']
        aez =  json_data.features[i]['properties']['AEZ']

    for j in range(len(coordlist)):
        for k in range(len(coordlist[j])):
            coordlist[j][k][0],coordlist[j][k][1]=m(coordlist[j][k][0],coordlist[j][k][1])
      
    poly = {"type":"Polygon","coordinates":coordlist}#coordlist
    color1 = a[region[name]-1,int(aez)-1,:]
    EK = 'none'
    if i>=2796:
        color1=[1,1,1,1]

    ax.add_patch(PolygonPatch(poly, fc=color1, ec=EK, zorder=2 ))

#Annotate
ax.set_title('SSP1 Maize Yield Improvement',fontsize=25,y=1.01)#GDP Adjusted Policy Cost#Policy Cost#Policy Cost Reduction from Technology
plt.annotate(2100,xy=(0.15,0.2),xytext=(0.15,0.2),xycoords='axes fraction',fontsize=30)
cb = m.colorbar(colors,'right')
cb.ax.tick_params(labelsize=14)
cb.set_label('Percent Change from Reference',fontsize=16,rotation=270,labelpad=20)#cb.set_label('Trillion 1990 USD',fontsize=16,rotation=270,labelpad=20)

#Save Figure
ax.axis('scaled')
plt.draw()
plt.show()
fig.savefig('test.pdf',format='pdf')