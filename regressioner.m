
data = csvread('output.csv');

% fileID = fopen('kc_house_test_data.csv');
% C = textscan(fileID,'%s');
% fclose(fileID);
% scatter(training_data(:,5),training_data(:,2));
% lsline
% x=1:102;%1:1000:17384;
% y=data(:,3);
% err=data(:,4);
% %x=1:size(y,1);
% errorbar(x,y,err,'-s','MarkerSize',10,...
%     'MarkerEdgeColor','red','MarkerFaceColor','red')

figure1 = figure;
plotregression_changed(data(:,2),data(:,3),'Regression');% R,yhat

