#include <iostream>
#include <fstream>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

template <typename T>

T getavg(T a, T b) //Template musi być z założenia wykładowcy
{
    T res;
    res = a / b;
    return res;
}

class Song
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
    ~Song() {}
};

class Album
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

class Artist
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
    ~Artist() {}
};

int main()
{
    string inputname;
    int simpleoradvance = 0;
    int choice;
    cout << "Do you want simple (1) or advanced (2) search method?." << endl << endl;
    cin >> simpleoradvance;
    cin.ignore();
    try  //Exception musi być z założenia wykładowcy
    {
        if (simpleoradvance > 2)
        {
            throw 1;
        }
    }
    catch(int number)
    {
        cout << "Error number " << number << endl;
    }

    Artist artistarr[500];
    Album albumarr[500];
    Song songarr[500];

    ifstream database("database.txt");
    string tempstring;
    string result;
    string tempword;
    string separr[6];
    int sepint = 0;
    int index=0;

    if (simpleoradvance == 2)
    {
        while (getline(database, tempstring))
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
            artistarr[index].setname(separr[0]);
            artistarr[index].setgenre(separr[4]);
            albumarr[index].setname(separr[1]);
            albumarr[index].setyear(stoi(separr[5]));
            songarr[index].setname(separr[2]);
            songarr[index].setBPM(stof(separr[3]));

            tempword = "";
            sepint = 0;
            fill_n(separr, 6, "");
            index++;
        }
        database.close();

        cout << "Search all songs from artist (1)" << endl;
        cout << "Search all songs from album (2)" << endl;
        cout << "Search all albums from artist (3)" << endl;
        cout << "Advanced parameter search (4)" << endl;
        cin >> choice;
        cin.ignore();

        try //Exception musi być z założenia wykładowcy
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

        float sumbpm = 0;
        float sumyear = 0;
        float count = 0;
        float avgbpm;
        int avgyear;
        bool disp = false;
        bool found = false;

        if (choice == 1)
        {
            cout << "Enter artist name: " << endl;
            getline(cin, inputname);
            cout << endl;
            for (int i = 0; i < index; i++)
            {
                if (artistarr[i].getname() == inputname)
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
                avgbpm = getavg<float>(sumbpm,count);
                cout << "Average BPM of a song from this artist is: " << avgbpm << endl;
            }
            else
            {
                cout << "No artist found." << endl;
            }

        }
        else if (choice == 2)
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
                avgbpm = getavg<float>(sumbpm, count);
                avgyear = getavg<int>(sumyear, count);
                cout << "Average BPM of a song in this album: " << avgbpm << endl;
                cout << "Average year: " << avgyear << endl;
            }
            else
            {
                cout << "No album found." << endl;
            }
        }
        else if (choice == 3)
        {
            string already;
            cout << "Enter artist name: " << endl;
            getline(cin, inputname);
            cout << endl;
            for (int i = 0; i < index; i++)
            {
                if (already != albumarr[i].getname())
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
            float maxbpm, minbpm;
            int maxyear, minyear;
            int choicenext;
            string genre;
            cout << "If you want to search a song from: " << endl;
            cout << "Particular artist (1)" << endl;
            cout << "Particular album (2)" << endl;
            cout << "No particular artist or album (3)" << endl;
            cin >> choicenext;
            cin.ignore();

            try //Exception musi być z założenia wykładowcy
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

            if (choicenext == 1)
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
                    avgbpm = getavg<float>(sumbpm,count);
                    avgyear = getavg<int>(sumyear,count);
                    cout << "Average BPM of a song from this artist with preset parameters is: " << avgbpm << endl;
                    cout <<  "Average year: " << avgyear << endl;
                }
                else
                {
                    cout << "No song found." << endl;
                }
            }

            else if (choicenext == 2)
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
                    avgbpm = getavg<float>(sumbpm, count);
                    avgyear = getavg<int>(sumyear, count);
                    cout << "Average BPM of a song in this album with preset parameters is: " << avgbpm << endl;
                    cout << "Average year: " << avgyear << endl;
                }
                else
                {
                    cout << "No song found." << endl;
                }
            }
            else if (choicenext == 3)
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
                    avgbpm = getavg<float>(sumbpm, count);
                    avgyear = getavg<int>(sumyear, count);
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
    else if (simpleoradvance == 1) // To jest właściwie bezużyteczne, wczesna wersja programu przed zmianą wymagań wykładowcy
    {
        
    }
    _CrtDumpMemoryLeaks();
}
