/*I wrote that code on Visual Studio
and ran on it */

#include<bits/stdc++.h>
using namespace std;

int FIFO(int pages[], int numberOfPages, int numberOfFrame)
{
unordered_set<int> currentPages;
queue<int> queueFifo;
int pageFaults = 0;

for (int c = 0; c < numberOfPages; c++)
{
if (currentPages.size() < numberOfFrame)
{
if (currentPages.find(pages[c]) == currentPages.end())
{
currentPages.insert(pages[c]);
pageFaults++;
queueFifo.push(pages[c]);
}
}
else
{
if (currentPages.find(pages[c]) == currentPages.end())
{
int page = queueFifo.front();
queueFifo.pop();

currentPages.erase(page);
currentPages.insert(pages[c]);
queueFifo.push(pages[c]);
pageFaults++;
}
}
}
return pageFaults;
}
int LRU(int pages[], int numberOfPages, int numberOfFrames)
{
unordered_set<int> currentPages;
unordered_map<int, int> pageIndexes;

int pageFaults = 0;

for (int c = 0; c < numberOfPages; c++)
{
if (currentPages.size() < numberOfFrames)
{
if (currentPages.find(pages[c]) == currentPages.end())
{
currentPages.insert(pages[c]);
pageFaults++;
}

pageIndexes[pages[c]] = c;
}
else
{
if (currentPages.find(pages[c]) == currentPages.end())
{
int lruPage = INT_MAX, page;

for (auto it = currentPages.begin(); it != currentPages.end(); it++)
{
if (pageIndexes[*it] < lruPage)
{
lruPage = pageIndexes[*it];
page = *it;
}
}
currentPages.erase(page);
currentPages.insert(pages[c]);
pageFaults++;
}
pageIndexes[pages[c]] = c;
}
}
return pageFaults;
}

bool search(int page, vector<int> &frames)
{
for (int c = 0; c < frames.size(); c++)
if (frames[c] == page)
return true;

return false;
}

int predict(int pages[], vector<int>& frames, int numberOfPages, int index)
{
int resentFuture = -1, farthestPage = index;

for(int c = 0; c < frames.size(); c++)
{
int d;
for(d = index; d < numberOfPages; d++)
{
if(frames[c] == pages[d])
{
if(d > farthestPage)
{
farthestPage = d;
resentFuture = c;
}
break;
}
}
if (d == numberOfPages)
return c;
}
return (resentFuture == -1) ? 0 : resentFuture;
}

void optimalPage(int pages[], int numberOfPages, int numberOfFrames)
{
vector<int> frames;

int numberOfHit = 0;

for(int c = 0; c < numberOfPages; c++)
{

if (search(pages[c], frames))
{
numberOfHit++;
continue;
}

if (frames.size() < numberOfFrames)
frames.push_back(pages[c]);

else
{
int d = predict(pages, frames, numberOfPages, c + 1);
frames[d] = pages[c];
}
}

cout<<"No. of hits = "<<numberOfHit<<endl;
cout<<"No. of misses = "<<numberOfPages - numberOfHit<<endl;
}

int menu()
{
int ch;
cout<<"\n\n ********************* MENU ********************* ";
cout<<"\n 1. First-In, First-Out (FIFO) \n 2. Least Recently Used (LRU) \n 3. Optimal (OPT) \n Exit";

cout<<"\n What is your choice? ";
cin>>ch;
return ch;
}

int main()
{
int pages[] = {1, 2, 1, 5, 0, 1, 0, 2, 2, 5, 0, 5, 2};
int numberOfPages = sizeof(pages)/sizeof(pages[0]);
int numberOfFrames = 4;

cout<<"\n Number of page fault: "<<FIFO(pages, numberOfPages, numberOfFrames)<<endl;
cout<<"\n Number of page fault: "<<LRU(pages, numberOfPages, numberOfFrames)<<endl;
cout<<"\n Number of page fault: ";
optimalPage(pages, numberOfPages, numberOfFrames);
return 0;
}

