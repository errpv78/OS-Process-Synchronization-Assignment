#include<bits/stdc++.h>
#include<thread>
#include<mutex>
#include<semaphore.h>
#include<queue>
#include<time.h>
#include<unistd.h>
using namespace std;

sem_t s_q1, s_q2, s_file;
queue<int> q1,q2;
int num_of_inserts=0,num_of_removes=0;

void producer(int pid)
{
    srand(time(0));
    ifstream file_r;
    ofstream file_w;
    while(1)
    {
        int choice = rand() % 2 == 0 ? 1 : 2;
        int n=rand()%51 +1;
        int sleep_time = rand()%3;
        string s="";
        if(choice==1)
        {
            cout<<"Producer process: "<<pid<<" trying to insert in q1\n";
            sem_wait(&s_file);
            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(pid-1,1,"1");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);

            sem_wait(&s_q1);

            sem_wait(&s_file);
            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(pid-1,1,"2");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);

            if(q1.size()<50)
            {
                q1.push(choice);
                num_of_inserts++;
            }

            sem_post(&s_q1);
            cout<<"Producer process: "<<pid<<" successfully inserted in q1\n";
            sem_wait(&s_file);
            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(pid-1,1,"0");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);

        }
        else if(choice==2)
        {
            cout<<"Producer process: "<<pid<<" trying to insert in q2\n";

            sem_wait(&s_file);
            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(10+pid-1,1,"1");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);

            sem_wait(&s_q2);

            sem_wait(&s_file);
            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(10+pid-1,1,"2");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);

            if(q2.size()<50)
            {
                q2.push(choice);
                num_of_inserts++;
            }


            sem_post(&s_q2);
            cout<<"Producer process: "<<pid<<" successfully inserted in q2\n";
            sem_wait(&s_file);
//            cout<<"File held by producer: "<<pid<<endl;
            file_r.open("matrix.txt");
            file_r>>s;
            file_r.close();
            file_w.open("matrix.txt");
            s.replace(10+pid-1,1,"0");
            file_w<<s;
            file_w.close();
            sem_post(&s_file);
        }
        sleep(sleep_time);
    }

}

void consumer(int pid, int p)
{
    srand(time(0));
    ifstream file_r;
    ofstream file_w;
    while(1)
    {
        int num_queues, choice = rand()%10;
        int sleep_time = rand()%6;
        string s="";
        if(p*10>choice)
        {
            int queue_choice = rand() % 2 == 0 ? 1 : 2;
            if(queue_choice == 1)
            {
                cout<<"Consumer Process: "<<pid<<" trying to consume (only from) q1\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q1);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q1.size()>0)
                {
                    q1.pop();
                    num_of_removes++;
                }

                sem_post(&s_q1);
                cout<<"Consumer Process: "<<pid<<" consumed from q1\n";

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);
            }
            else
            {
                cout<<"Consumer Process: "<<pid<<" trying to consume (only from) q2\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q2);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q2.size()>0)
                {
                    q2.pop();
                    num_of_removes++;
                }

                sem_post(&s_q2);
                cout<<"Consumer Process: "<<pid<<" consumed from q1\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);
           }
        }
        else
        {
            int first = rand() % 2 == 0 ? 1 : 2;
            if(first == 1)
            {
                cout<<"Consumer Process: "<<pid<<" first trying to consume from q1\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q1);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q1.size()>0)
                {
                    q1.pop();
                    num_of_removes++;
                }
                cout<<"Consumer Process: "<<pid<<" second trying to consume from q2\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q2);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q2.size()>0)
                {
                    q2.pop();
                    num_of_removes++;
                }


                sem_post(&s_q1);
                cout<<"Consumer Process: "<<pid<<" consumed from q1\n";

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);


                sem_post(&s_q2);
                cout<<"Consumer Process: "<<pid<<" consumed from q2\n";

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);
            }

            else
            {
                cout<<"Consumer Process: "<<pid<<" first trying to consume from q2\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q2);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q2.size()>0)
                {
                    q2.pop();
                    num_of_removes++;
                }

                cout<<"Consumer Process: "<<pid<<" second trying to consume from q1\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"1");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_wait(&s_q1);

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"2");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                if(q1.size()>0)
                {
                    q1.pop();
                    num_of_removes++;
                }


                sem_post(&s_q2);
                cout<<"Consumer Process: "<<pid<<" consumed from q2\n";

                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(15+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

                sem_post(&s_q1);
                cout<<"Consumer Process: "<<pid<<" consumed from q1\n";
                sem_wait(&s_file);
                cout<<"File held by consumer: "<<pid<<endl;
                file_r.open("matrix.txt");
                file_r>>s;
                file_r.close();
                file_w.open("matrix.txt");
                s.replace(5+pid-1,1,"0");
                file_w<<s;
                file_w.close();
                sem_post(&s_file);

            }
        }
        sleep(sleep_time);
    }
}
void print()
{
    while(1)
    {
        cout<<"No of removes: "<<num_of_removes<<endl;
        cout<<"No of insertions: "<<num_of_inserts<<endl;
        sleep(2);

    }
}

int main()
{
  sem_init(&s_file, 0, 1);
  sem_init(&s_q1, 0, 1);
  sem_init(&s_q2, 0, 1);

  ifstream file_r;
  ofstream file_w;
  file_w.open("matrix.txt");
  for(int i=0;i<2;i++)
  {
    for(int j=0;j<10;j++)
    {
      file_w<<0;
    }
  }
  file_w.close();
  int p;
  cout<<"\nEnter probability (0-1): ";
  cin>>p;

  int p1=1,p2=2,p3=3,p4=4,p5=5;
  int c1=1,c2=2,c3=3,c4=4,c5=5;
  std::thread t1(producer, 1);
  std::thread t2(producer, 2);
  std::thread t3(producer, 3);
  std::thread t4(producer, 4);
  std::thread t5(producer, 5);
  std::thread t6(consumer, 1,p);
  std::thread t7(consumer, 2,p);
  std::thread t8(consumer, 3,p);
  std::thread t9(consumer, 4,p);
  std::thread t10(consumer, 5,p);
  std::thread t11(print);
  string s;
  while(1)
  {
    sem_wait(&s_file);
    cout<<"File held by deadlock\n";
    file_r.open("matrix.txt");
    s = "";
    file_r>>s;
    file_r.close();
    int q1_2=-1,q2_2=-1;
    for(int i=5;i<10;i++)
    {
        if(s[i]=='2' && s[i+10]=='1')
        {
            q1_2 = i-4;
            for(int j=15;j<20;j++)
            {
                if(s[j]=='2' && s[j-10]=='1')
                {
                    q2_2 = j-14;
                    cout<<"\nDeadlock:\n";
                    cout<<"\nIn q1 process with id: "<<q1_2<<" is holding q1 and asking for q2.\n";
                    cout<<"\nIn q2 process with id: "<<q2_2<<" is holding q2 and asking for q1.\n";
                    cout<<"\nNumber of inserts: "<<num_of_inserts<<endl;
                    cout<<"\nNumber of removes: "<<num_of_removes<<endl;
                    exit(0);

                }
            }

        }
    }
    sem_post(&s_file);
    cout<<"\nFile released by deadlock\n";
    sleep(2);
  }

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
}
