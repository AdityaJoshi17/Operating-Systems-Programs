#include<iostream>
using namespace std;

int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
 	for(i = 1; i < n; ++i)
	{
        if(time[i] < minimum)
		{
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
    cout<<"Enter number of frames: ";
    cin>>no_of_frames;

    cout<<"Enter number of pages: ";
    cin>>no_of_pages;

    cout<<"Enter reference string: ";

    for(i = 0; i < no_of_pages; ++i)
	{
        cin>>pages[i];
    }

    for(i = 0; i < no_of_frames; ++i)
	{
        frames[i] = -1;
    }

    for(i = 0; i < no_of_pages; ++i)  //This loop processes each page in the reference string.
	{
        flag1 = flag2 = 0;

        for(j = 0; j < no_of_frames; ++j) //It checks if the current page is already present in the frames.
        //If found, it updates the counter and time, and sets flags to indicate that the page is found.
		{
            if(frames[j] == pages[i])
			{
                counter++;      // Page is found in frames.
                time[j] = counter;    // Update counter and time.
                flag1 = flag2 = 1;    // Set flags.
                break;
            }
        }

        if(flag1 == 0) //Page Not Found in Frames:
		{
            for(j = 0; j < no_of_frames; ++j)
			{
                if(frames[j] == -1)   //// Check for empty frames.
                //// If empty frame found, add the page.
				{
                    counter++;
                    faults++;     //// Update counter and faults.
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0)   //All Frames Occupied:
		{
            pos = findLRU(time, no_of_frames); // Find the LRU page using findLRU function.
            counter++;// Replace the LRU page with the current page.
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter; // Update counter and faults.
        }

        cout<<"\n";

        for(j = 0; j < no_of_frames; ++j)
		{
            cout<<"\t"<<frames[j];
        }
    }

    cout<<"\n\nTotal Page Faults ="<<faults;
    return 0;
}
