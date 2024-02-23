cd 'C:\Users\omart\Downloads';

Data = readtable('feed.csv');

plot(Data.entry_id, Data.field1, 'LineWidth', 2, 'DisplayName', 'LM35');
hold on;
plot(Data.entry_id, Data.field2, 'LineWidth', 2, 'DisplayName', 'OpenWeather API');
plot(Data.entry_id, Data.field3, 'LineWidth', 2, 'DisplayName', 'Difference');

xlabel('Entry ID');
ylabel('Field Values');
title('Plot of LM35, OpenWeatherAPI, and Difference over Entry ID');
legend('Location', 'Best');
grid on;
hold off;