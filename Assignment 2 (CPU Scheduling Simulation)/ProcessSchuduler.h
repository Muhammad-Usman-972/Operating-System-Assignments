#include<iostream>
#include<fstream>
#include<list>
#include<iterator>
#include <sstream>
#include<queue>
using namespace std;



struct process
{
	string name;
	int time;
	int burst;
	string state;
	string instructions;
	int index;
	bool jump;
	process()
	{
		name = "\0";
		time = 0;
		state = "New";
		instructions = "";
		burst = 0;
		index = 0;
		jump = false;
	}
	process(string n, int t, string s, string i, int b, int in, bool j)
	{
		index = in;
		name = n;
		time = t;
		state = s;
		instructions = i;
		burst = b;
		jump = j;

	}
	int getindex()
	{
		return this->index;
	}


};


list<process> process_list;
priority_queue<int, vector<int>, greater<int> > q;

//Waiting queues
queue<int> DISK;
queue<int> SCREEN;
queue<int> NETWORK;
//Ready queues
queue<int> FCFS_1;
queue<int> FCFS_2;
priority_queue<int, vector<int>, greater<int> > SJF;


int calculate_burst_time(string file)
{
	ifstream read_file;
	string str;
	int burst_time = 0;
	read_file.open(file.append(".txt"), ios::in);
	if (!(read_file))
	{
		cout << "Error in opening file";
		return 0;
	}
	else
	{/*
		cout << "Instructions of " <<file << " is : \n";*/
		while (1)
		{
			if (read_file.eof())
			{
				break;
			}
			getline(read_file, str);
			if (str == "COMPUTE")
			{
				burst_time++;
			}
			else if (str == "READ SCREEN")
			{
				burst_time += 2;
			}
			else if (str == "WRITE NETWORK")
			{
				burst_time += 3;
			}
			else if (str == "WRITE DISK")
			{
				burst_time += 2;
			}
			else if (str == "End")
			{
				break;
			}
			/*cout << str << endl;*/
		}
		/*cout << "\nBurst time = " << burst_time << endl;*/
	}
	return burst_time;
}

void runProcessScheduling(const char* PathofJobFile, int globalTick)
{
	process p_obj;

	int local_tick = 0;
	int cpu_time = 3;
	string line, proc, arrival;
	int time = 0;
	int proc_count = 0;

	ifstream read_file;

	read_file.open("job.txt", ios::in);
	if (!(read_file))
	{
		cout << "Error in opening file" << endl;
	}
	else
	{

		while (1)
		{
			if (read_file.eof())
			{
				break;
			}

			read_file >> proc >> arrival;
			proc_count++;

			/*cout << "Process = " << proc << "\nArrival time = " << arrival << endl;*/
			time = stoi(arrival); // String to int typecasting
			q.push(time);

			/*process p_obj(proc,time);
			process_list.push_back(p_obj);
			size = process_list.size();
			process temp = process_list.front();*/

		}

		//Finally i have inserted all things in linked list , Alhamdullilah
		int index = 0;
		ofstream write;
		write.open("Process.txt", ios::app);
		ifstream file;
		while (!q.empty())
		{
			process p_obj;
			time = q.top();
			string n = to_string(time);
			string p = "P";
			p_obj.name = p.append(n);
			p_obj.time = time;
			p_obj.burst = calculate_burst_time(p);
			p_obj.state = "new";
			p_obj.index = index;
			write << "index:\t" << index << "\tname: " << p << "\ttime: " << n << "\tstate: " << p_obj.state << endl;
			file.open(p_obj.name.append(".txt"), ios::in);
			if (file.is_open())
			{
				while (getline(file, line))
				{
					/*cout << line << endl;*/
					if (line != " ")
					{
						p_obj.instructions.append(line + "\n");
					}

				}
			}
			/*cout << p_obj.instructions << endl;*/
			file.close();
			process_list.push_back(p_obj);
			index++;
			q.pop();
		}

		//Insertion starts now


		int temp_time = 0;

		list<process> ::iterator ite1;

		int ind = 0;
		int size = 0;
		int chk = 0;
		bool sq = false;
		ofstream queue_write;
		queue_write.open("Queue.txt", ios::app);


		for (ite1 = process_list.begin(); ite1 != process_list.end() && local_tick <= globalTick;)
		{
			sq = false;
			if (local_tick == ite1->time)
			{
				FCFS_1.push(ite1->index);
				queue_write << "FCFS-1 \t" << ite1->index << endl;
				if (size < process_list.size())
				{
					ite1++;
					size++;
				}
			}
			list<process> ::iterator ite2;
			ofstream cpu;
			cpu.open("CPU.txt", ios::app);
			process current;

			for (ite2 = process_list.begin(); ite2 != process_list.end(); ite2++)
			{
				if (sq == true)
				{
					break;
				}
				if (FCFS_1.front() == ite2->index)
				{
					temp_time = 0;
					string line;
					std::istringstream iss(ite2->instructions);
					/*cout << ite2->instructions << endl;*/
					cout << "Name: " << ite2->name << "in FCFS-1" << endl;
					cpu << endl;
					cpu << ite2->name << "\t";
					chk = 0;

					while (getline(iss, line) && temp_time <= cpu_time)
					{

						if (line == "")
						{
							continue;
						}
						cout << line << endl;
						if (ite2->burst == 0)
						{
							cout << "Process " << ite2->name << "has been executed!" << endl;
							break;

						}
						/*ite2->instructions.replace(ite2->instructions.find(line), line.length(), "");*/

						if (line == "COMPUTE")
						{
							cpu << line << "\t";
							chk++;
							ite2->burst--;
							ite2->instructions.replace(ite2->instructions.find(line), line.length(), "");
						}
						else if (line == "READ SCREEN")
						{
							cpu << line << "\t";
							/*cout << line << endl;*/
							chk = 0;
							if (ite2->jump == true)
							{

								ite2->burst -= 2;
								ite2->instructions.replace(ite2->instructions.find(line), line.length(), "");
								SCREEN.push(ite2->index);
								ite2->jump = false;
							}
							else
							{

								ite2->jump = true;
								break;
							}
						}
						else if (line == "WRITE NETWORK")
						{
							cpu << line << "\t";
							chk = 0;
							if (ite2->jump == true)
							{

								ite2->burst -= 3;
								ite2->instructions.replace(ite2->instructions.find(line), line.length(), "");
								NETWORK.push(ite2->index);
								ite2->jump = false;
							}
							else
							{
								ite2->jump = true;
								break;
							}
						}
						else if (line == "WRITE DISK")
						{
							cpu << line << "\t";
							chk = 0;
							if (ite2->jump == true)
							{

								ite2->burst -= 2;
								ite2->instructions.replace(ite2->instructions.find(line), line.length(), "");
								DISK.push(ite2->index);
							}
							else
							{
								ite2->jump = true;
								break;
							}


						}
						else if (line == "End")
						{
							cpu << line << "\t";
							break;
						}
						else
						{
							cpu << endl;
							continue;
						}
						if (chk == 3)
						{
							sq = true;
							cout << ite2->burst << endl;
							queue_write << "FCFS-2\t" << ite2->index << endl;
							FCFS_2.push(ite2->index);
							break;
						}
						temp_time++;
						cout << ite2->burst << endl;
					}

					FCFS_1.pop();


					if (ite2->burst > 0 && ite2->jump == true)
					{
						FCFS_1.push(ite2->index);
						queue_write << "FCFS-1\t" << ite2->index << endl;

					}

				}
			}


			local_tick++;
		}


	}
	read_file.close();

}
int main()
{
	int global_tick = 30;
	runProcessScheduling("job.txt", global_tick);
}
