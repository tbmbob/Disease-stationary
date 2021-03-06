#define PERSON_BUFFER 100
#define NUM_PEOPLE    1000000
#define DAYS_INFECTED 10
//#define EXP_PARAMETER 53.0
#define EXP_PARAMETER 70.0
#define POW_ALPHA     4
//#define POW_R_0       50.0
#define POW_R_0       70.0
#define SUSCEPTIBLE   0
#define RECOVERED     -1
#define MAX_SIM_TIME  300

#include <queue>
#include <vector>

class World
{
public:
  typedef struct person {
    // 0 = Susceptible
    // 1 - 254 = Infected
    // 255 = Dead/safe/recovered
    char status;
    double x;
    double y;
  } person;

  World();
  virtual ~World();

  person* get_people();
  int get_count();
  int print_people(person[]);
  bool step();

private:
  int generate_people(person **, int);
  int populate_person_rand(person *);
  int populate_person_grid(person *, int, int, int);
  int populate_people(person *, int);
  int print_person(char *, person *);
  bool contact_occurs(person, person);
  double toroidal_distance(double, double, double, double);
  int infect(int);
  int cure(int);
  int progress_sickness(int);
  int populate_matrix(unsigned long **, person *, int, double (World::*)(double));
  unsigned long exp_contact(person *, person *, double (World::*)(double));
  double linear_dist(double);
  double exp_dist(double);
  double pow_dist(double);

  //A list of all people that exist.
  person* master_list;
  //The total number of people
  int master_count;
  //A 2d-array listing how long each person would take to infect the others
  unsigned long **master_matrix;
  // Numbers of people infected, susceptible, or recovered
  int num_i;
  int num_s;
  int num_r;

  //keeps track of the current simulation time, in steps
  int simtime;
  /*
     template< typename FirstType, typename SecondType >
     struct PairComparator {
     bool operator()( const std::pair<FirstType, SecondType>& p1,
     const std::pair<FirstType, SecondType>& p2 ) const 
     {    
     return p1.second > p2.second;
     }
     }
     */
  struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
      return left.second > right.second;
    }
  };  

  typedef std::priority_queue< std::pair<int, int>, std::vector<std::pair<int,int> >, sort_pred > personPQ;

  std::vector<person*> infected;
  personPQ master_queue;
  
};
