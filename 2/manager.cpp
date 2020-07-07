#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<semaphore.h>
#include<queue>
#include<time.h>
#include<unistd.h>
#include<string>
using namespace std;

sem_t s_n,s_s,s_e,s_w,s_junc,s_file;
int num_trains_completed=0;

void train(int pid, string direction)
{
    cout<<"\nTrain process created with pid: "<<pid;
    ifstream file_r;
    ofstream file_w;
    string s;
    if(direction=="N")
    {
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);
        cout<<"\nNorth train requests North lock process id:"<<pid;
        sem_wait(&s_n);
        cout<<"\nNorth train acquires North lock process id "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4,1,"2");
        s.replace(pid*4+1,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nNorth train requests West lock process id: "<<pid;
        sem_wait(&s_w);
        cout<<"\nNorth train acquires West lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+1,1,"2");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nNorth train requests Junction lock process id: "<<pid;
        sem_wait(&s_junc);
        cout<<"\nNorth train acquires Junction lock process id: "<<pid;

        sleep(2);

        sem_post(&s_junc);
        cout<<"\nNorth train releases Junction lock process id: "<<pid;

        sem_post(&s_w);
        cout<<"\nNorth train releases West lock process id: "<<pid;

        sem_post(&s_n);
        cout<<"\nNorth train releases North lock process id: "<<pid;
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4,1,"0");
        s.replace(pid*4+1,1,"0");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);
    }
    else if(direction=="W")
    {
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+1,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nWest train requests West lock process id: "<<pid;
        sem_wait(&s_w);
        cout<<"\nWest train acquires West lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+1,1,"2");
        s.replace(pid*4+2,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nWest train requests South lock process id: "<<pid;
        sem_wait(&s_s);
        cout<<"\nWest train acquires South lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+2,1,"2");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nWest train requests Junction lock process id: "<<pid;
        sem_wait(&s_junc);
        cout<<"\nWest train acquires Junction lock process id: "<<pid;

        sleep(2);

        sem_post(&s_junc);
        cout<<"\nWest train releases Junction lock process id: "<<pid;

        sem_post(&s_s);
        cout<<"\nWest train releases South lock process id: "<<pid;
        sem_post(&s_w);
        cout<<"\nWest train releases West lock process id: "<<pid;
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+1,1,"0");
        s.replace(pid*4+2,1,"0");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

    }
    else if(direction=="S")
    {
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+2,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nSouth train requests South lock process id: "<<pid;
        sem_wait(&s_s);
        cout<<"\nSouth train acquires South lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+2,1,"2");
        s.replace(pid*4+3,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nSouth train requests East lock process id: "<<pid;
        sem_wait(&s_e);
        cout<<"\nSouth train acquires East lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+3,1,"2");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nSouth train requests Junction lock process id: "<<pid;
        sem_wait(&s_junc);
        cout<<"\nSouth train acquires Junction lock process id: "<<pid;

        sleep(2);

        sem_post(&s_junc);
        cout<<"\nSouth train releases Junction lock process id: "<<pid;

        sem_post(&s_e);
        cout<<"\nSouth train releases East lock process id: "<<pid;
        sem_post(&s_s);
        cout<<"\nSouth train releases South lock process id: "<<pid;
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+2,1,"0");
        s.replace(pid*4+3,1,"0");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

    }
    else if(direction=="E")
    {
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+3,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nEast train requests East lock process id: "<<pid;
        sem_wait(&s_e);
        cout<<"\nEast train acquires East lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+3,1,"2");
        s.replace(pid*4,1,"1");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nEast train requests North lock process id: "<<pid;
        sem_wait(&s_n);
        cout<<"\nEast train acquires North lock process id: "<<pid;

        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4,1,"2");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

        cout<<"\nEast train requests Junction lock process id: "<<pid;
        sem_wait(&s_junc);
        cout<<"\nEast train acquires Junction lock process id: "<<pid;

        sleep(2);

        cout<<"\nEast train releases Junction lock process id: "<<pid;
        sem_post(&s_junc);

        sem_post(&s_n);
        cout<<"\nEast train releases North lock process id: "<<pid;
        sem_post(&s_e);
        cout<<"\nEast train releases East lock process id: "<<pid;
        sem_wait(&s_file);
        s="";
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        file_w.open("matrix.txt");
        s.replace(pid*4+3,1,"0");
        s.replace(pid*4,1,"0");
        file_w<<s;
        file_w.close();
        sem_post(&s_file);

    }
    cout<<"\nTrain process completed with pid: "<<pid;
    num_trains_completed++;
}


int main()
{
  sem_init(&s_file, 0, 1);
  sem_init(&s_n, 0, 1);
  sem_init(&s_s, 0, 1);
  sem_init(&s_e, 0, 1);
  sem_init(&s_w, 0, 1);
  sem_init(&s_junc, 0, 1);

  ifstream file_r;
  ofstream file_w;
  file_r.open("sequence.txt");
  string sequence;
  file_r>>sequence;
  cout<<sequence;
  file_r.close();
  int num_trains=sequence.length();

  file_w.open("matrix.txt");
  string mat="";
  for(int i=0;i<num_trains*4;i++)
  {
    mat+="0";
  }
  file_w<<mat;
  file_w.close();
  int p;
  cout<<"\nEnter probability p (0-1) (probability of checking deadlock): ";
  cin>>p;
  int num_trains_created=0;
  srand(time(0));
  string s;
  int count_of_deadlock_checks=0;
  while(1)
  {
    if(num_trains_created<num_trains)
    {
        int choice=rand()%10;
        if(choice<p)
        {
            sem_wait(&s_file);
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            bool north=false,west=false,south=false,east=false;
            int t_n,t_w,t_s,t_e;
            for(int i=0;i<num_trains;i++)
            {
                cout<<s<<endl;
                if(s[(4*i)]=='2' && s[(4*i)+1]=='1')
                {
                    north=true;
                    t_n=i+1;
                }
                if(s[4*i+1]=='2' && s[4*i+2]=='1')
                {
                    west=true;
                    t_w=i+1;
                }
                if(s[4*i+2]=='2' && s[4*i+3]=='1')
                {
                    south=true;
                    t_s=i+1;
                }
                if(s[4*i+3]=='2' && s[4*i]=='1')
                {
                    east=true;
                    t_e=i+1;
                }
                if(north==true && west==true && south==true && east==true)
                {
                    cout<<"\nDeadlock detected: \n";
                    cout<<"Number of train process created: "<<num_trains_created<<endl;
                    cout<<"\nTrain from north: "<<t_n;
                    cout<<"\nTrain from west: "<<t_w;
                    cout<<"\nTrain from south: "<<t_s;
                    cout<<"\nTrain from east: "<<t_e;
                    exit(0);
                }
            }
            sem_post(&s_file);
        }
        else
        {
            string c;
            c=sequence[num_trains_created];
            std::thread t1(train, num_trains_created, c);
            t1.detach();
            num_trains_created++;
        }
    }

    else
    {
        if(num_trains_completed>=num_trains)
        {
            cout<<"No deadlocks\nAll processes completed successfully:";
            exit(0);
        }
        sem_wait(&s_file);
        file_r.open("matrix.txt");
        file_r>>s;
        file_r.close();
        bool north=false,west=false,south=false,east=false;
        int t_n,t_w,t_s,t_e;
        for(int i=0;i<num_trains;i++)
        {
            if(s[4*i]=='2' && s[4*i+1]=='1')
            {
                north=true;
                t_n=i+1;
            }
            if(s[4*i+1]=='2' && s[4*i+2]=='1')
            {
                west=true;
                t_w=i+1;
            }
            if(s[4*i+2]=='2' && s[4*i+3]=='1')
            {
                south=true;
                t_s=i+1;
            }
            if(s[4*i+3]=='2' && s[4*i]=='1')
            {
                east=true;
                t_e=i+1;
            }
            if(north==true && west==true && south==true && east==true)
            {
                cout<<"\nDeadlock detected: \n";
                cout<<"Number of train process created: "<<num_trains_created<<endl;
                cout<<"\nTrain from north: "<<t_n;
                cout<<"\nTrain from west: "<<t_w;
                cout<<"\nTrain from south: "<<t_s;
                cout<<"\nTrain from east: "<<t_e;
                exit(0);
            }
        }
        sem_post(&s_file);
        sleep(1);
    }

  }
  while(1);
//  t[0].join();
}
