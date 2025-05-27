# Final-Project: UPeel Me

## A novel game that simulates the experience of a Filipino University student “Isko/Iska” in a one-week period before their final examinations. 

This project offers a realistic and engaging simulation of the challenges students face during intense study. Unlike typical visual novels with many branching storylines, its gameplay centers on strategically managing four key variables: hunger, knowledge acquisition, happiness, and energy. Your daily decisions and random events within the game affect these factors. To succeed on final exams, you need to balance your overall well-being with your academic preparation. The project's ultimate aim is to portray the internal struggles and external pressures that significantly influence a student's academic performance when facing tight deadlines.


## How to Compile

1. Prerequisites

   Before you can compile, ensure you have the following installed on your system:

   A C compiler:

   * **Linux/macOS:** gcc (part of GCC) or clang (part of LLVM) are commonly available.
     You might need to install build-essential (Ubuntu/Debian-based systems) or Xcode Command Line Tools (macOS) to get them.
   * **Windows:** MinGW-w64 (provides gcc and g++)
     Visual Studio with the "Desktop development with C++" workload (provides MSVC compiler, cl.exe)

2. Getting the Code

   First, clone the repository to your local machine:  
   ```
   git clone https://github.com/Emanwel/Final-Project.git  
   ```
3. Compiling and Running the Program

   After a successful compilation, you can choose to:

   * **Execute the standalone application:** Find the compiled .exe (or equivalent executable file on Linux/macOS) in the build output directory and run it directly.
   * **Launch from the IDE:** Utilize your IDE's built-in run functionality, which will typically recompile if necessary and then execute the program immediately.


## How to Play: UPeel Me (Isko/Iska Simulator)

Welcome, Isko/Iska! Get ready to experience the intense, often unpredictable, week leading up to your final exams. This game challenges you to strategically balance your academic duties with your personal well-being to achieve the best possible outcome in your finals.

### The Goal

Your ultimate objective is to **successfully navigate the one-week period** before your final examinations and **achieve a positive outcome on your finals**. Every decision you make will impact your chances of success.

### Core Mechanics

The game revolves around managing **four crucial player attributes** that reflect your student life:

* **Knowledge on Subject:** This represents your academic preparedness. The higher your knowledge, the better equipped you are for exams.
* **Happiness:** This reflects your emotional and psychological well-being. A happy Isko/Iska is a more efficient Isko/Iska!
* **Energy:** This indicates your physical and mental stamina. You need energy to study, socialize, and simply get through the day.
* **Hunger:** This tracks your need for sustenance. Neglecting your hunger can negatively impact your other stats and overall performance.

### Your Week: Day by Day

The game progresses day by day over a **one-week timeframe**. Each day, you'll be presented with **daily choices** that directly impact your Knowledge, Happiness, Energy, and Hunger levels. These choices might include:

* Studying for different subjects
* Taking breaks or relaxing
* Eating meals 
* Socializing with friends
* Sleeping

Choose wisely! Every decision comes with consequences, affecting your attributes by varying point amounts.

### Expect the Unexpected: Random Events

Life as an Isko/Iska is rarely straightforward. Throughout the week, **unexpected random events** will occur. These events can offer opportunities to gain points in your attributes or, conversely, present challenges that might deplete them. Adaptability is key!

### Strategic Planning is Crucial

The heart of the game lies in **strategic planning**. You need to find the optimal balance:

* **Don't just study!** While knowledge is vital, neglecting your Hunger, Happiness, and Energy can lead to burnout, poor concentration, and ultimately, poor performance.
* **Don't just relax or eat!** Too much leisure and food without studying will leave you unprepared for exams.
* **Manage your resources.** Use your Energy effectively to accomplish tasks that benefit you most, and ensure you're eating regularly to keep hunger at bay.

Your final exam outcome will directly reflect how well you managed these core aspects throughout the week. Good luck, Isko/Iska – your finals await!

## Sample Input/Output:

" You decide what to do with your time.  
  Input one of these keywords to continue.

STATS - Show how much energy you have for the day  
STUDY - Stidy for your upcoming test  
GAMES - Play a game of Lihokang Leyenda: Buto Buto  
FRIENDS - Talk to your friends about their plans for the day  
TIME - Check your watch  
OUTSIDE - Go to a place  
SLEEP - Take a 1hr nap (sleeps through the night when sleeping at home by 21:00)  

\>> SLEEP **[INPUT]**


You took a nap for an hour to refresh your senses. **[OUTPUT]**"
