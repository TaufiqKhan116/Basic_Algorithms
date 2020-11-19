#include <iostream>
#include <vector>

using namespace std;

/*
Activity Selection Problem :
        Given a set of activities each marked by a start time (si) and finish time (fi), the problem is to select the maximum number of activities
    that can be performed by a single person or machine, assuming that a person can only work on a single activity at a time. The activity selection
    problem is also known as the Interval scheduling maximization problem (ISMP).

Procedure :
        Firstly, we have to sort the activities on basis of their finish time in ascending order. The first activity in the sorted list will always be
    included into solution. Then, we will traverse rest of the array. If the finish time of lastly included activity is smaller than the starting time of
    activity in the array, we will include the activity to solution.

Sample Input :
6
0 6
3 4
1 2
5 9
5 7
8 9

Sample Output :
Activities can be done without overlapping :
Activity : 2
Activity : 1
Activity : 4
Activity : 5

References :
        Youtube => https://youtu.be/poWB2UCuozA
        Wikipedia => https://en.wikipedia.org/wiki/Activity_selection_problem
*/

typedef struct Activity { //Activity
    int activityTitle;
    int startTime;
    int finishTime;
};
vector<Activity> v; //Output vector

void activitySelection(Activity arr[], int size) {
    v.push_back(arr[0]); //First activity from sorted array always included

    //For rest of the activities in the array, if their start time is greater then the finish time of last activity included into output vector then include it too
    for(int i = 1; i < size; i++)
        if(arr[i].startTime > v[v.size() - 1].finishTime)
            v.push_back(arr[i]);
}

int main()
{
    int n;
    Activity arr[100]; //Activity list

    cout << "Enter activity number and start time and finish time :" << endl;
    cin >> n;
    for(int i = 0; i < n; i++) {
        arr[i].activityTitle = i;
        cin >> arr[i].startTime;
        cin >> arr[i].finishTime;
    }

    //Sorting activities on basis of finish time
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(arr[j].finishTime <= arr[i].finishTime) {
                Activity tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }

    activitySelection(arr, n);

    cout << "Activities can be done without overlapping :" << endl;
    for(int i = 0; i < v.size(); i++)
            cout << "Activity : " <<v[i].activityTitle << endl;
    return 0;
}
