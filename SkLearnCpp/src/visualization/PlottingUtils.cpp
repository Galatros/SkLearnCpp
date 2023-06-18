#include "../../include/visualization/PlottingUtils.h"

void plotDecisionRegions(const std::vector<std::vector<double>>& X, const std::vector<int>& y, const std::vector<std::vector<double>>& X_test, const std::vector<int>& y_test, Classifier& classifier) {
    std::ofstream gnuplotScript("decision_regions.gp");

    if (gnuplotScript.is_open()) {
        // Set up the meshgrid
        double x1_min = std::numeric_limits<double>::max();
        double x1_max = std::numeric_limits<double>::min();
        double x2_min = std::numeric_limits<double>::max();
        double x2_max = std::numeric_limits<double>::min();
        for (const auto& row : X) {
            if (row[0] < x1_min) x1_min = row[0];
            if (row[0] > x1_max) x1_max = row[0];
            if (row[1] < x2_min) x2_min = row[1];
            if (row[1] > x2_max) x2_max = row[1];
        }

        double resolution = 0.005;//0.02
        std::vector<double> xx1, xx2;
        for (double x1 = x1_min - 0.3; x1 <= x1_max + 0.3; x1 += resolution) {//1
            for (double x2 = x2_min - 0.3; x2 <= x2_max + 0.3; x2 += resolution) {//1
                xx1.push_back(x1);
                xx2.push_back(x2);
            }
        }

        // Generate predictions for the meshgrid points
        std::vector<int> Z;
        for (size_t i = 0; i < xx1.size(); ++i) {
            int prediction = classifier.predict(std::vector<double>{xx1[i], xx2[i]});
            Z.push_back(prediction);
        }

        // Write the Gnuplot script
        gnuplotScript << "set terminal wxt\n";
        gnuplotScript << "unset key\n";
        gnuplotScript << "unset tics\n";
        gnuplotScript << "set palette defined (0 'red', 1 'yellow', 2 'blue')\n";
        gnuplotScript << "set style circle radius 0.02\n";//0.09
        gnuplotScript << "set xrange[" << x1_min - 0.3 << ":" << x1_max + 0.3 << "]\n";
        gnuplotScript << "set yrange[" << x2_min - 0.3 << ":" << x2_max + 0.3 << "]\n";

        // Plot decision regions
        gnuplotScript << "plot '-' with points lc variable pt 7 notitle, ";

        // Plot training data points
        gnuplotScript << "'-' using 1:2:3 with points lc palette pt 7 title 'Training Set', ";

        // Plot test data points
        gnuplotScript << "'-' using 1:2:3 with points lc palette pt 7 title 'Test Set',";

        // Plot test data circles
        gnuplotScript << "'-' using 1:2 with circles lc rgb 'white' title 'Test Set Circle'\n";

        // Write meshgrid data
        for (size_t i = 0; i < xx1.size(); ++i) {
            gnuplotScript << xx1[i] << " " << xx2[i] << " " << Z[i] << std::endl;
        }
        gnuplotScript << "e\n";

        // Write training data points
        for (size_t i = 0; i < X.size(); ++i) {
            gnuplotScript << X[i][0] << " " << X[i][1] << " " << y[i] << std::endl;
        }
        gnuplotScript << "e\n";

        // Write test data points
        for (size_t i = 0; i < X_test.size(); ++i) {
            gnuplotScript << X_test[i][0] << " " << X_test[i][1] << " " << y_test[i] << std::endl;
        }
        gnuplotScript << "e\n";

        // Write test data circles
        for (size_t i = 0; i < X_test.size(); ++i) {
            gnuplotScript << X_test[i][0] << " " << X_test[i][1] << " " << y_test[i] << std::endl;
        }
        gnuplotScript << "e\n";

        gnuplotScript.close();

        std::string saveCommand = "gnuplot -e \"load 'decision_regions.gp'; set terminal png; set output 'decision_regions.png'; replot; pause -1\"";
        system(saveCommand.c_str());
    }
    else {
        std::cout << "Unable to create Gnuplot script file.\n";
    }
}