close all
clc
clear all

% Define Color Palette
clr = [ 228,26,28;
        55,126,184;
        77,175,74;
        152,78,163;255,127,0;255,255,51;166,86,40;247,129,191;153,153,153]*(1/255);

% Load Data
holder = xlsread('..\data\data.csv');
holder_SSP = xlsread('..\data\SSP-SPA-CF.csv');
a = holder(:,7);

%% Generate Figures
figure1=figure;
axes1 = axes('Parent',figure1,'FontSize',15,'FontName','Times New Roman');
hold(axes1,'on');

%Plot sampled points first
for i = 1:3
    I = a+1 == i;
    for j = 1:3
        clrs(I,j) = clr(i,j);
    end
    scatter(holder(I,10)*100,holder(I,11),100,clrs(I,:),'.')
end

%Plot the canonical SSPs in black for the legend
scatter(holder_SSP(1,1)*100,holder_SSP(1,2),150,'ok','MarkerFaceColor','k')
scatter(holder_SSP(3,1)*100,holder_SSP(3,2),150,'^k','MarkerFaceColor','k')
scatter(holder_SSP(5,1)*100,holder_SSP(5,2),150,'vk','MarkerFaceColor','k')
scatter(holder_SSP(6,1)*100,holder_SSP(6,2),150,'dk','MarkerFaceColor','k')
scatter(holder_SSP(8,1)*100,holder_SSP(8,2),150,'sk','MarkerFaceColor','k')

%Plot the canonical SSPs in the color corresponding to different CFs
scatter(holder_SSP(1,1)*100,holder_SSP(1,2),150,'o','MarkerFaceColor',clr(4,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(2,1)*100,holder_SSP(2,2),150,'o','MarkerFaceColor',clr(5,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(3,1)*100,holder_SSP(3,2),150,'^','MarkerFaceColor',clr(4,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(4,1)*100,holder_SSP(4,2),150,'^','MarkerFaceColor',clr(5,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(5,1)*100,holder_SSP(5,2),150,'v','MarkerFaceColor',clr(5,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(6,1)*100,holder_SSP(6,2),150,'d','MarkerFaceColor',clr(4,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(7,1)*100,holder_SSP(7,2),150,'d','MarkerFaceColor',clr(5,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(8,1)*100,holder_SSP(8,2),150,'s','MarkerFaceColor',clr(4,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)
scatter(holder_SSP(9,1)*100,holder_SSP(9,2),150,'s','MarkerFaceColor',clr(5,:),'MarkerEdgeColor',[0.4,0.4,0.4]*0.5)

%Plot the CF colored banding
x = [0,1.4];
y_44 = [4.4,4.4];
y_46 = [4.6,4.6];
y_59 = [5.9,5.9];
y_61 = [6.1,6.1];

s1 = fill([x,fliplr(x)],[y_44,fliplr(y_46)],clr(4,:),'EdgeColor','none');
s2 = fill([x,fliplr(x)],[y_59,fliplr(y_61)],clr(5,:),'EdgeColor','none');

alpha(s1,0.5)
alpha(s2,0.5)

%Add labels
xlabel('2020-2095 Average Global Policy Cost (% GDP)','FontSize',20,'FontName','Times New Roman')
ylabel('Forcing (W/m^2)','FontSize',20,'FontName','Times New Roman')
legend1=legend('Low LT Price','High LT Price','No Price','SSP1','SSP2','SSP3','SSP4','SSP5');
set(legend1,...
    'Position',[0.20308027107385 0.700065722667972 0.151356990501627 0.193495033068589],...
    'FontSize',13.5);
set(figure1,'pos',[0,50,1000,1000])
hold(axes1,'off');