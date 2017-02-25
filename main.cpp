/*
 * prog8_acd21.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: Adam
 */
/*
 * prog8_acd21.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: Adam C. De Leon
 *      Net ID: acd21
 *      Description: This program is intended for use in assisting a local
 *      community with a half-marathon race. Race officials will create a text
 *      file (half_marathon.txt) which contains on the first line the total
 *      number of runners and on each subsequent line, the runners ID's,
 *      runner gender, and runner completion times. Runner times of 0 indicate
 *      that the runner did not complete the race in time. The text file
 *      half_marathon.txt is read in by the program as an input file. The
 *      program then validates that the output file (prog8_out_acd21.txt) was
 *      created. The program then processes the rest of the information before
 *      finally displaying two separate lists; one with a list of male runner
 *      ID's, a sentence displaying the runner ID and the fastest runner time,
 *      and finally another sentence displaying the average finishing time,
 *      while the second list displays the corresponding results for female
 *      runners.
 *
 *      Return 1 - Error code, displays that the output file could not be
 *      		   created.
 *      Return 2 - Error code, displays that the input file could not be
 *      		   found.
 */

# include <iostream>
# include <fstream>
# include <iomanip>

using namespace std;

/*Prototypes for program*/
int GetMarathonData(int[], char[], double[], int);

int GetFastest(char[], double[], int, char);

double GetAverage(char[], double[], int, char, int &);

int main() {
    /*Declare constants, arrays, and variables*/
    const int MAX_RUNNERS = 50;
    int runner_id[MAX_RUNNERS];
    char gender[MAX_RUNNERS];
    double runner_time[MAX_RUNNERS];
    int num_runners;
    char m_or_f;
    int fastest_male;
    int fastest_female;
    double male_average;
    double female_average;
    int male_finishers;
    int female_finishers;
    int finishers;

    /*output stream object.*/
    ofstream fout;

    /*Open the output file.*/
    fout.open("prog8_out_acd21.txt");

    /*Validate that the output file was created correctly.*/
    if (!fout) {
        cout << "The output file could not be created.";
        return 1;
    }

    /*call the GetMarathonData function to get the number of runners.*/
    num_runners = GetMarathonData(runner_id, gender, runner_time,
                                  num_runners);

    /*Validate that the input file was opened, and provide an early return .*/
    if (num_runners == -1) {
        cout << "Input file could not be found.";
        return 2;
    }

        /*If input file was opened successfully run the rest of the program.*/
    else
        fout << "Male Runners:" << endl;
    fout << endl;

    /*Output the list of male runner ID's.*/
    for (int i = 0; i < num_runners; i++) {
        if (gender[i] == 'M') {
            fout << runner_id[i];
            fout << endl;
        }
    }
    fout << endl;

    /*Call the GetFastest function to get data needed to output the ID of the
     * fastest male runner and the time that he ran the race in.*/
    fastest_male = GetFastest(gender, runner_time, num_runners, 'M');
    fout << "Runner " << runner_id[fastest_male] << " has the fastest time of "
         << runner_time[fastest_male] << " minutes." << endl;

    /*Call the GetAverage function to get the data needed to output the
     * average elapsed time for male runners that finished the race.*/
    male_average = GetAverage(gender, runner_time, num_runners, 'M',
                              male_finishers);
    fout << setprecision(1) << fixed;
    fout << "The average time for male finishers is " << male_average <<
         " minutes. " << endl;
    fout << endl;

    fout << "Female Runners:" << endl;
    fout << endl;

    /*Output the list of female runner ID's*/
    for (int i = 0; i < num_runners; i++) {
        if (gender[i] == 'F') {
            fout << runner_id[i];
            fout << endl;
        }
    }
    fout << endl;

    /*Call the Getfastestfunction to get data needed to output the ID of the
     * fastest male runner and the time that he ran the race in. */
    fastest_female = GetFastest(gender, runner_time, num_runners, 'F');
    fout << endl;

    fout << "Runner " << runner_id[fastest_female] << " has the fastest time "
            "of " << runner_time[fastest_female] << " minutes." << endl;

    /*Call the GetAverage function to get the data needed to output the
     * average elapsed time for female runners that finished the race.*/
    female_average = GetAverage(gender, runner_time, num_runners, 'F',
                                female_finishers);

    fout << "The average time for female finishers is " << female_average <<
         " minutes. " << endl;
    fout << endl;

    /*Output the total number of people who finished the race.*/
    finishers = (male_finishers + female_finishers);
    fout << finishers << " out of " << num_runners << " runners finished the "
            "race." << endl;

    /*Close the output file*/
    fout.close();
    return 0;
}

/*****************************************************************************
 * GetMarathonData - This function handles all of the input including opening
 * closing, and validating the input file. 4th parameter is the
 * maximum size of the arrays. The function returns the number of actual
 * runners. If the input file fails to open the number of runners is
 * initialized to negative one.
 */
int GetMarathonData(int runner_id[], char gender[], double runner_time[],
                    int num_runners) {
    ifstream fin;
    fin.open("half_marathon.txt");
    if (!fin) {
        num_runners = -1;
    } else
        fin >> num_runners;

    for (int i = 0; i < num_runners; i++) {
        fin >> runner_id[i];
        fin >> gender[i];
        fin >> runner_time[i];
    }
    fin.close();
    return num_runners;
}

/*****************************************************************************
 * GetFastest - This function has as its parameters two parallel arrays,
 * including the number of actual runners, and a character indicating whether
 * or not they are looking at male or female runners. It returns the array
 * index of the runner having the fastest time.
 */
int GetFastest(char gender[], double runner_time[], int count, char m_or_f) {
    int location;
    double fastest;
    fastest = 1000;
    for (int j = 0; j < count; j++) {
        if (gender[j] == m_or_f && runner_time[j] != 0) {
            if (runner_time[j] < fastest) {
                fastest = runner_time[j];
                location = j;
            }
        }
    }
    return location;
}

/*****************************************************************************
 * GetAverage - This function has as its parameters two parallel arrays, the
 * number of actual runners, a character indicating whether or not the average
 * is for male or female runners and an integer parameter that is passed by
 * reference in which the number of male or female finishers is returned. It
 * returns the average of all finishing runners having the indicated gender
 * and returns the number of actual finishers with that gender in its last
 * parameter.
 */

double GetAverage(char gender[], double runner_time[], int count,
                  char m_or_f, int &finishers) {
    double average;
    double sum;
    int tally;
    sum = 0;
    tally = 0;

    for (int k = 0; k < count; k++) {
        if (gender[k] == m_or_f && runner_time[k] != 0) {
            sum = sum + runner_time[k];
            tally = tally + 1;
        }
    }
    average = sum / tally;
    finishers = tally;
    return average;
}




