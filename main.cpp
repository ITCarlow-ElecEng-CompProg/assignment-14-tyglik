/** Lab 14 - File Processing
 *  Martina Nunvarova
 *  24/01/2018
 *
 *
 * To process input file, calculate and display min,max,avg,sdev to user
 * To allow user to specify to sort data in ascending or descending order (not specified how)
 * To save sorted data in a file.
 *
 * User input through command line - parametre:
 *          file.exe ASC
 *          file.exe dEScendingDont care what follows the first letter
 */

 ///includes
#include <iostream>
#include <fstream>
#include <math.h>       ///sqrt

///namespace
using namespace std;

///compare function for ascending choice
bool isGreaterThan(double a,double b)
{
    return a>b;
}

///compare function for descending choice
bool isLeserThan(double a,double b)
{
    return isGreaterThan(b,a);
}

///main function - expects parametres
int main(int argc, char *argv[])
{
    ///variables
    ofstream oF;
    ifstream iF;
    int nrCount=0,i,j;
    string line;
    double *nrList;                         ///need dynamic array - don't know the size of input - not given!
    double n,minN,maxN,avgN=0,stdD=0;
    bool (*compare)(double a, double b);    ///pointer to sorting function - faster than "if (choice='A') else"

    ///inform user: 1) you can run this with a parametre;
    if (argc<2)
        cout <<"To change the sorting, run this program with a parametre."<<endl
             <<"None or incorrect choice defaults to Ascending order."<<endl<<endl
             << ":/> Lab14-FileSort.exe [ A(scending) | D(escending) ]"<<endl<<endl
             <<"**********************************************************"<<endl;

    ///inform user: 2) I'm working on it
    cout <<"Processing file:"<<endl;

    ///open input file;
    iF.open("rawValues.txt");

    ///find how many numbers (lines) we deal with
    while (getline(iF,line)) {
                                            ///let the user know about the progress
        if (! (nrCount%100000))             ///every 100000 records display a dot
            cout <<".";
        nrCount++;                          ///while counting the rows (numerical entries)
    }

//    iF.seekg(0);                            ///reset position in fire - return to beginning - does not seem to work
    iF.close();                             ///close the file
    iF.open("rawValues.txt");               ///and open again (alternative to iF.seekg())

    nrList=new double[nrCount];             ///create an array of required size
    if (nrList == NULL) {                   ///If you failed
        cout <<endl<< "Error creating the array!"<<endl<<endl;  ///let the user know
        return 1;                           ///and exit to OS with return code 1
    }

    ///find min, max, avg
    i=0;
    while (!iF.eof() && i<nrCount) {        /// repeat until you hit the end of file, but no more than the space in the array
        iF >>nrList[i];                     ///and read in all the numbers
        if (i==0) {
            minN=nrList[i];                 ///just assign the >>first<< number to be both min and max
            maxN=nrList[i];
        } else {
            if (minN>nrList[i])             ///any other number is compared and if min or max then remembered as such
                minN=nrList[i];
            if (maxN<nrList[i])
                maxN=nrList[i];
        }
        avgN+=nrList[i];                    ///sum the numbers for average
        if (! (i%100000))                   ///Let the user know something is happening
            cout <<".";                     ///every 100000 records display a dot
        i++;
    }
    iF.close();                             ///finished with the input file, close it.

    avgN/=nrCount;                          ///turn sum into average

    for (i=0;i<nrCount-1;i++)
        stdD+=(nrList[i]-avgN)*(nrList[i]-avgN);    /// SUM( (x - xbar)^2 )
    stdD=sqrt(stdD/(nrCount-1));                    ///last step to obtain std deviation

    ///inform the user and print the statistical values - on screen only
    cout <<endl<< "Input file is processed. "<<endl
         <<"**********************************************************"<<endl<<endl
         << "Statistics:"<<endl
         <<"Min: "<<minN<<"       Max: "<<maxN<<"       Avg: "<<avgN<<endl
         <<"Std.Dev.: "<<stdD<<endl<<endl;


    ///find out if user made a choice in sorting, and if it d
    if (argc>1 && argv[1] && (argv[1][0]=='d' ||argv[1][0]=='D'))
        compare = &isLeserThan;                         ///select the sorting function according to user choice
    else
        compare = &isGreaterThan;

    ///sort the array
    for (i=0;i<nrCount-1;i++)
        for (j=i+1;j<nrCount;j++)
            if (compare(nrList[i],nrList[j])) {         ///number in beginning is larger than the one near end?
                n=nrList[i];                            ///so SWAP THEM
                nrList[i]=nrList[j];
                nrList[j]=n;
            }

    ///print the sorted array into file
    oF.open("sortedValues.txt");                        ///open the output file
    for (i=0;i<nrCount;i++) {
        oF<<nrList[i]<<endl;                            ///write all the array (numbers) into it
//        cout << nrList[i]<<endl;                        ///and on screen for debug
    }
    oF.close();                                         ///then close the file

    delete [] nrList;                                   ///free the array from memory
    return 0;                                           ///return to OS, no errors
}
