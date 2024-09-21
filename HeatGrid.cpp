/*
This class will create a 2d array and initialize it with temperature values
come up with equation for initial temperatures
    create normal distribution
    find max value
    arrange numbers by abslute value distance from max value
#did not generate distribution of temps to pull from,
#Chose a max temp for center cell and greated gradient of temp difference using euclidean distance
#Now I will generate equation to update temps at time intervals using FINITE DIFFERENCE METHOD
#the best approach may be to ignore conrners of grid and assign boundary conditions
#this will allow for simplest application of finite difference method
#current implementation only updates inner cells
visualize with matplotlib wrapper
*/

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

const int TEMPARRAYLENGTH = 100;

// double getTempMax(double tempArray[][TEMPARRAYLENGTH]);

void generateTempGrid(double maxTemp, double tempArray[][TEMPARRAYLENGTH]);
void printTempGrid(double tempArray[][TEMPARRAYLENGTH]);
void updateTempGrid(int iterations, double tempArray[][TEMPARRAYLENGTH]);

int main()
{

    // default_random_engine tempGenerator;

    // normal_distribution<double> tempDist(50.0, 25.0);

    double tempArray[TEMPARRAYLENGTH][TEMPARRAYLENGTH];

    double tempMax = 100.00;

    bool update = true;

    char response;

    int iterations, threads;
    threads = 0;

    cout << "**********************\n";
    cout << "HEAT DIFFUSION SIMULATOR\n";
    cout << "**********************\n";

    cout << "This program models heat diffusion in a steady state system being heated from the center.\n";
    cout << "It updates cell values with double precision floating point arithmetic, utilizing openMP to showcase the power of parallel processing.\n";
    cout << "Play with the program using 1 processor, then start over and use multiple to see the difference in performance.\n";
    cout << "If you have a modern processor differences will not be obvious unless you run 100k+ iterations.\n";
    cout << "If you would like to see the values being updated. Open the output1.txt file that will be created in this directory and refresh it each round.\n";

    // cout << "Press c to continue, press l to learn more, press q to quit";

    // cin >> response;

    // if (response = 'c')
    // {
    //     system("cls");
    // }
    // else if (response = 'l')
    // {
    //     cout << "This program models a steady state system that is being heated from the center, it uses multithreading to optimize the process according to user specifications.";
    //     cout << "Press c to continue or q to quit.";
    //     cin >> response;
    //     if (response = 'c')
    //     {
    //         system("cls");
    //     }
    //     else
    //         return 0;
    // }
    // else
    //     return 0;

    cout << "Please assign the number of processors you would like to operate in parallel: ";

    cin >> threads;

    omp_set_num_threads(threads);

    generateTempGrid(tempMax, tempArray);
    printTempGrid(tempArray);

    while (update = true)
    {
        cout << "Type a number to apply desired number of iterations or 0 to quit: ";
        cin >> iterations;

        updateTempGrid(iterations, tempArray);
        printTempGrid(tempArray);

        if (iterations == 0)
        {
            update = false;
            break;
        }
    }

    // for (int i = 0; i < 20; i++)
    // {
    //     for (int j = 0; j < 20; j++)
    //     {
    //         outFile << fixed << setprecision(2) << "\t" << (20 - abs(10 - j));
    //     }
    // }

    // outFile.close();

    return 0;
}

// double getTempMax(double tempArray[][TEMPARRAYLENGTH])
// {
//     double tempMax = 0;
//     for (int i = 0; i < 100; i++)
//     {
//         for (int j = 0; j < 100; j++)
//             if (tempArray[i][j] > tempMax)
//             {
//                 tempMax = tempArray[i][j];
//             }
//     }
//     return tempMax;
// }

void generateTempGrid(double maxTemp, double tempArray[][TEMPARRAYLENGTH])
{
    for (int i = 0; i < TEMPARRAYLENGTH; i++)
    {
        for (int j = 0; j < TEMPARRAYLENGTH; j++)
        {
            int distance = sqrt(pow((i - 19), 2) + pow((j - 19), 2));
            tempArray[i][j] = maxTemp - 3 * distance; //(abs((19 * 2) - (i + j)));
        }
    }
}

void printTempGrid(double tempArray[][TEMPARRAYLENGTH])
{
    ofstream outFile;
    outFile.open("HeatGrid.csv");

    for (int i = 0; i < TEMPARRAYLENGTH; i++)
    {
        for (int j = 0; j < TEMPARRAYLENGTH; j++)
        {
            // tempArray[i][j] = tempDist(tempGenerator);
            outFile << fixed << setprecision(2) << "\t" << tempArray[i][j];
        }
        outFile << "\n";
    }
    outFile.close();
}

void updateTempGrid(int iterations, double tempArray[][TEMPARRAYLENGTH])
{
#pragma omp parallel for
    for (int i = 0; i < iterations; i++)
    {
        // cout << "Number of threads used: " << omp_get_num_threads();
        for (int j = 1; j < TEMPARRAYLENGTH - 1; j++)
        {
            for (int k = 1; k < TEMPARRAYLENGTH - 1; k++)
            {
                tempArray[j][k] = (tempArray[j + 1][k] + tempArray[j - 1][k] + tempArray[j][k + 1] + tempArray[j][k - 1]) / 4;
            }
        }
    }
    cout << "Temperatures updated\n";
}
