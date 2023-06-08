#include <iostream>
#include <fstream>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

template <typename T>

T getavg(T a, T b) //template function used to calculate average of two variables of type T, used in parameters of songs
{
    T res;
    res = a / b;
    return res;
}

class Song //class storing all the necessary information about the song
{
private:
    string songname;
    float BPM;
public:
    void setname(string input)
    {
        songname = input;
    }
    string getname()
    {
        return songname;
    }
    void setBPM(float input)
    {
        BPM = input;
    }
    float getBPM()
    {
        return BPM;
    }
    ~Song() 
    {
    }
};

class Album //class storing all the necessary information about the album
{
private:
    string albumname;
    int year;
public:
    void setname(string input)
    {
        albumname = input;
    }
    string getname()
    {
        return albumname;
    }
    void setyear(int input)
    {
        year = input;
    }
    int getyear()
    {
        return year;
    }
    ~Album() {}
};

class Artist //class storing all the necessary information about the song
{
private:
    string artistname;
    string genre;
public:
    void setname(string input)
    {
        artistname = input;
    }
    string getname()
    {
        return artistname;
    }
    void setgenre(string input)
    {
        genre = input;
    }
    string getgenre()
    {
        return genre;
    }
    ~Artist() 
    {
    }
};

void displayseparated() //user can display whole database with this function
{
    ifstream database("database.txt"); //stream from file
    string tempstring; //temporary string 
    string result; //variable to make sure input is untouched
    string tempword; //temporary string added to separation array elements
    string separr[6]; //separation array to get data one
    int sepint = 0; //separation array index
    while (getline(database, tempstring))
    {
        result = tempstring;
        for (int i = 0; i < result.size(); i++)
        {
            if (result[i] != ';') //adding word when it meets semicolon
            {
                tempword += result[i];
            }
            else
            {
                separr[sepint] += tempword;
                tempword = "";
                sepint++;
            }
        }

        for (int o = 0; o < 3; o++) //display
        {
            cout << separr[o] << endl;
        }
        tempword = ""; //clearing temporary string
        sepint = 0; //going back to the beggining of array since this is index
        fill_n(separr, 6, ""); //clearing separation array
        cout << endl << endl;
    }
    database.close();
}

int main()
{
    {
        string inputname; //to be entered by a user
        int disporadvance = 0; //choice variable 
        int choice; //choice variable 
        cout << "Do you want to display all songs (1) or enter advanced search enginge (2)?." << endl << endl;
        cin >> disporadvance;    //First level of menu choice
        cin.ignore();
        try //exceptions to handle wrong input from user
        {
            if (disporadvance > 2)
            {
                throw 1;
            }
        }
        catch (int number)
        {
            cout << "Error number " << number << endl;
        }

        Artist artistarr[500];
        Album albumarr[500];
        Song songarr[500];

        ifstream database("database.txt"); //input from file
        string tempstring; //temporary string 
        string result; //variable to make sure input is untouched
        string tempword; //temporary string added to separation array elements
        string separr[6]; //separation array to get data one
        int sepint = 0; //separation array index
        int index = 0; // --- Aditional index to move through objects inside of arrays ---

        if (disporadvance == 2)
        {
            while (getline(database, tempstring)) //reading data from .txt to arrays
            {
                result = tempstring;
                for (int i = 0; i < result.size(); i++)
                {
                    if (result[i] != ';')
                    {
                        tempword += result[i];
                    }
                    else
                    {
                        separr[sepint] += tempword;
                        tempword = "";
                        sepint++;
                    }
                }
                artistarr[index].setname(separr[0]); //using class functions to set parameters for each object
                artistarr[index].setgenre(separr[4]);
                albumarr[index].setname(separr[1]);
                albumarr[index].setyear(stoi(separr[5]));
                songarr[index].setname(separr[2]);
                songarr[index].setBPM(stof(separr[3]));

                tempword = ""; //clearing temporary string
                sepint = 0; //going back to the beggining of array since this is index
                fill_n(separr, 6, ""); //clearing array
                index++; //increasing index to move to next object
            }
            database.close();

            cout << "Search all songs from artist (1)" << endl;
            cout << "Search all songs from album (2)" << endl;
            cout << "Search all albums from artist (3)" << endl;
            cout << "Advanced parameter search (4)" << endl;
            cin >> choice;    //Second level of menu choice
            cin.ignore();

            try //exception handling in case of wrong input from keyboard
            {
                if (choice > 4)
                {
                    throw 2;
                }
            }
            catch (int number)
            {
                cout << "Error number " << number << endl;
            }

            float sumbpm = 0; //input from file
            float sumyear = 0; //temporary string 
            float count = 0; //number of occurences
            float avgbpm; //average bpm value
            int avgyear; //average year value
            bool disp = false;
            bool found = false;

            if (choice == 1) //Searching all songs from particular artist
            {
                cout << "Enter artist name: " << endl;
                getline(cin, inputname);
                cout << endl;
                for (int i = 0; i < index; i++) //moving through object array
                {
                    if (artistarr[i].getname() == inputname) //comparing input with actual array
                    {
                        found = true;
                        sumbpm += songarr[i].getBPM();
                        sumyear += albumarr[i].getyear();
                        count++;
                        if (disp == false)
                        {
                            cout << artistarr[i].getname() << " is of genre " << artistarr[i].getgenre() << endl << endl;
                            disp = true;
                        }
                        cout << songarr[i].getname() << "   -   BPM: " << songarr[i].getBPM() << endl;
                    }
                }
                if (found)
                {
                    cout << endl;
                    avgbpm = getavg<float>(sumbpm, count);
                    cout << "Average BPM of a song from this artist is: " << avgbpm << endl;
                }
                else
                {
                    cout << "No artist found." << endl;
                }

            }
            else if (choice == 2) //Searching all songs from a particular album
            {
                cout << "Enter album name: " << endl;
                getline(cin, inputname);
                cout << endl;
                for (int i = 0; i < index; i++)
                {
                    if (albumarr[i].getname() == inputname)
                    {
                        found = true;
                        sumbpm += songarr[i].getBPM();
                        sumyear += albumarr[i].getyear();
                        count++;
                        if (disp == false)
                        {
                            cout << albumarr[i].getname() << " is of genre " << artistarr[i].getgenre() << " and came out in " << albumarr[i].getyear() << endl << endl;
                            disp = true;
                        }
                        cout << songarr[i].getname() << "   -   BPM: " << songarr[i].getBPM() << endl;
                    }
                }
                if (found)
                {
                    cout << endl;
                    avgbpm = getavg<float>(sumbpm, count); //average tempo
                    cout << "Average BPM of a song in this album: " << avgbpm << endl; 
                }
                else
                {
                    cout << "No album found." << endl;
                }
            }
            else if (choice == 3) //Searching all albums from a particular artist
            {
                string already; //string to prevent albums from duplicating
                cout << "Enter artist name: " << endl;
                getline(cin, inputname);
                cout << endl;
                for (int i = 0; i < index; i++)
                {
                    if (already != albumarr[i].getname()) //checking whether the album already exists
                    {
                        if (artistarr[i].getname() == inputname)
                        {
                            found = true;
                            if (disp == false)
                            {
                                cout << artistarr[i].getname() << " is of genre " << artistarr[i].getgenre() << endl << endl;
                                disp = true;
                            }
                            cout << albumarr[i].getname() << endl;
                            already = albumarr[i].getname();
                        }
                    }
                }
                if (found == false)
                {
                    cout << "No album found." << endl;
                }
            }
            else if (choice == 4)
            {
                float maxbpm, minbpm; //advanced searching parameters regarding tempo
                int maxyear, minyear; //advanced searching parameters regarding year
                int choicenext; //choice variable
                string genre; //advanced searching parameter regarding genre
                cout << "If you want to search a song from: " << endl;
                cout << "Particular artist (1)" << endl;
                cout << "Particular album (2)" << endl;
                cout << "No particular artist or album (3)" << endl;
                cin >> choicenext; //Third level of menu choice
                cin.ignore();

                try //exception handling
                {
                    if (choicenext > 3)
                    {
                        throw 3;
                    }
                }
                catch (int number)
                {
                    cout << "Error number " << number << endl;
                }

                //Getting parameters from user keyboard
                cout << "Enter parameters: " << endl; 
                cout << "Minimum BPM of the song: " << endl;
                cin >> minbpm;
                cin.ignore();
                cout << "Maximum BPM of the song: " << endl;
                cin >> maxbpm;
                cin.ignore();
                cout << "Minimum year of the song release: " << endl;
                cin >> minyear;
                cin.ignore();
                cout << "Maximum year of the song release: " << endl;
                cin >> maxyear;
                cin.ignore();
                cout << "Genre: " << endl;
                cin >> genre;
                cin.ignore();

                if (choicenext == 1) //Searching songs articular artist (1)
                {
                    cout << "Enter artist name: " << endl;
                    getline(cin, inputname);
                    cout << endl;
                    for (int i = 0; i < index; i++)
                    {
                        if (artistarr[i].getname() == inputname)
                        {
                            if (disp == false)
                            {
                                cout << artistarr[i].getname() << " is of genre " << artistarr[i].getgenre() << endl << endl;
                                disp = true;
                            }
                            if (minbpm <= songarr[i].getBPM() && songarr[i].getBPM() <= maxbpm && minyear <= albumarr[i].getyear() && albumarr[i].getyear() <= maxyear && genre == artistarr[i].getgenre())
                            {
                                found = true;
                                sumbpm += songarr[i].getBPM();
                                sumyear += albumarr[i].getyear();
                                count++;
                                cout << songarr[i].getname() << "   -   BPM: " << songarr[i].getBPM() << endl;
                            }
                        }
                    }
                    if (found)
                    {
                        cout << endl;
                        avgbpm = getavg<float>(sumbpm, count); //average tempo
                        avgyear = getavg<int>(sumyear, count); //average year
                        cout << "Average BPM of a song from this artist with preset parameters is: " << avgbpm << endl;
                        cout << "Average year: " << avgyear << endl;
                    }
                    else
                    {
                        cout << "No song found." << endl;
                    }
                }

                else if (choicenext == 2) //Searching songs articular album (2)
                {
                    cout << "Enter album name: " << endl;
                    getline(cin, inputname);
                    cout << endl;
                    for (int i = 0; i < index; i++)
                    {
                        if (albumarr[i].getname() == inputname)
                        {
                            if (disp == false)
                            {
                                cout << albumarr[i].getname() << " is of genre " << artistarr[i].getgenre() << " and came out in " << albumarr[i].getyear() << endl << endl;
                                disp = true;
                            }
                            if (minbpm <= songarr[i].getBPM() && songarr[i].getBPM() <= maxbpm && minyear <= albumarr[i].getyear() && albumarr[i].getyear() <= maxyear && genre == artistarr[i].getgenre())
                            {
                                found = true;
                                sumbpm += songarr[i].getBPM();
                                sumyear += albumarr[i].getyear();
                                count++;
                                cout << artistarr[i].getname() << " - " << songarr[i].getname() << "   -   BPM: " << songarr[i].getBPM() << endl;
                            }
                        }
                    }
                    if (found)
                    {
                        cout << endl;
                        avgbpm = getavg<float>(sumbpm, count); //average tempo
                        avgyear = getavg<int>(sumyear, count); //average year
                        cout << "Average BPM of a song in this album with preset parameters is: " << avgbpm << endl;
                        cout << "Average year: " << avgyear << endl;
                    }
                    else
                    {
                        cout << "No song found." << endl;
                    }
                }
                else if (choicenext == 3) //Searching songs in general (3)
                {
                    for (int i = 0; i < index; i++)
                    {
                        if (minbpm <= songarr[i].getBPM() && songarr[i].getBPM() <= maxbpm && minyear <= albumarr[i].getyear() && albumarr[i].getyear() <= maxyear && genre == artistarr[i].getgenre())
                        {
                            found = true;
                            sumbpm += songarr[i].getBPM();
                            sumyear += albumarr[i].getyear();
                            count++;
                            cout << artistarr[i].getname() << " - " << songarr[i].getname() << "   -   BPM: " << songarr[i].getBPM() << endl;
                        }
                    }
                    if (found)
                    {
                        cout << endl;
                        avgbpm = getavg<float>(sumbpm, count); //average tempo
                        avgyear = getavg<int>(sumyear, count); //average year
                        cout << "Average BPM of a song in this preset parameters is: " << avgbpm << endl;
                        cout << "Average year of a song release with preset parameters is: " << avgyear << endl;
                    }
                    else
                    {
                        cout << "No song found." << endl;
                    }
                }
            }
        }
        else if (disporadvance == 1) //displaying all the data
        {
            displayseparated();
        }
    }
    _CrtDumpMemoryLeaks();
    return 0;
}