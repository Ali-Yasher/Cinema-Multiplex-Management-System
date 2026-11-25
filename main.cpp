#include <iostream>
#include <string>

using namespace std;

class Movie {
private:
    string title;
    int runtimeMinutes;
    string distributor;

public:
    Movie() {
        title = "Untitled";
        runtimeMinutes = 90;
        distributor = "Independent";
    }

    Movie(string t, int runtime, string dist) {
        title = t;
        setRuntimeMinutes(runtime);
        distributor = dist;
    }

    Movie(const Movie& other) {
        title = other.title;
        runtimeMinutes = other.runtimeMinutes;
        distributor = other.distributor;
    }

    void setRuntimeMinutes(int runtime) {
        if (runtime > 0) {
            runtimeMinutes = runtime;
        }
    }

    string getTitle() const { return title; }
    int getRuntimeMinutes() const { return runtimeMinutes; }
    string getDistributor() const { return distributor; }

    void showDetails() const {
        cout << "Movie: " << title << " (" << runtimeMinutes << " min) | Distributor: " << distributor << endl;
    }
};

class ScreenHall {
private:
    string hallName;
    string hallClass; // "Silver", "Gold", "Platinum"
    int rows;
    int cols;
    double basePrice;

public:
    ScreenHall() {
        hallName = "Hall_01";
        hallClass = "Silver";
        rows = 5;
        cols = 5;
        basePrice = 10.0;
    }

    ScreenHall(string name, string hClass, int r, int c, double price) {
        hallName = name;
        setHallClass(hClass);
        setRows(r);
        setCols(c);
        setBasePrice(price);
    }

    ScreenHall(const ScreenHall& other) {
        hallName = other.hallName;
        hallClass = other.hallClass;
        rows = other.rows;
        cols = other.cols;
        basePrice = other.basePrice;
    }

    void setHallClass(string hClass) {
        if (hClass == "Silver" || hClass == "Gold" || hClass == "Platinum") {
            hallClass = hClass;
        } else {
            hallClass = "Silver";
        }
    }

    void setRows(int r) {
        if (r > 0) {
            rows = r;
        }
    }

    void setCols(int c) {
        if (c > 0) {
            cols = c;
        }
    }

    void setBasePrice(double price) {
        if (price >= 0.0) {
            basePrice = price;
        }
    }

    string getHallName() const { return hallName; }
    string getHallClass() const { return hallClass; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    double getBasePrice() const { return basePrice; }
    int getSeatCapacity() const { return rows * cols; }

    void showDetails() const {
        cout << "Hall: " << hallName << " | Class: " << hallClass
             << " | Grid: " << rows << "x" << cols
             << " (" << getSeatCapacity() << " seats) | Price: $" << basePrice << endl;
    }
};

class Show {
private:
    Movie movie;
    ScreenHall hall;
    int startMinutes;   // Minutes from midnight (e.g., 18:00 = 1080)
    int cleaningMinutes;

public:
    Show() {
        startMinutes = 600;
        cleaningMinutes = 15;
    }

    Show(Movie m, ScreenHall h, int startMin, int cleanMin) {
        movie = m;
        hall = h;
        setStartMinutes(startMin);
        setCleaningMinutes(cleanMin);
    }

    Show(const Show& other) {
        movie = other.movie;
        hall = other.hall;
        startMinutes = other.startMinutes;
        cleaningMinutes = other.cleaningMinutes;
    }

    void setStartMinutes(int startMin) {
        if (startMin >= 0 && startMin < 1440) {
            startMinutes = startMin;
        }
    }

    void setCleaningMinutes(int cleanMin) {
        if (cleanMin >= 0) {
            cleaningMinutes = cleanMin;
        }
    }

    Movie getMovie() const { return movie; }
    ScreenHall getHall() const { return hall; }
    int getStartMinutes() const { return startMinutes; }
    int getCleaningMinutes() const { return cleaningMinutes; }

    int calculateEndMinutes() const {
        return startMinutes + movie.getRuntimeMinutes() + cleaningMinutes;
    }

    void showDetails() const {
        int sH = startMinutes / 60;
        int sM = startMinutes % 60;
        int endTotal = calculateEndMinutes();
        int eH = (endTotal / 60) % 24;
        int eM = endTotal % 60;

        cout << "Show: " << movie.getTitle() << " in " << hall.getHallName()
             << " [" << hall.getHallClass() << "] | "
             << sH << ":" << (sM < 10 ? "0" : "") << sM
             << " - " << eH << ":" << (eM < 10 ? "0" : "") << eM << endl;
    }
};

class Scheduler {
private:
    Show* shows;
    int count;
    int capacity;

public:
    Scheduler() {
        capacity = 10;
        count = 0;
        shows = new Show[capacity];
    }

    Scheduler(const Scheduler& other) {
        capacity = other.capacity;
        count = other.count;
        shows = new Show[capacity];
        for (int i = 0; i < count; i++) {
            shows[i] = other.shows[i];
        }
    }

    ~Scheduler() {
        delete[] shows;
    }

    int getShowCount() const { return count; }

    bool checkOverlap(const Show& newShow) const {
        int newStart = newShow.getStartMinutes();
        int newEnd = newShow.calculateEndMinutes();

        for (int i = 0; i < count; i++) {
            if (shows[i].getHall().getHallName() == newShow.getHall().getHallName()) {
                int oldStart = shows[i].getStartMinutes();
                int oldEnd = shows[i].calculateEndMinutes();
                if (newStart < oldEnd && newEnd > oldStart) {
                    return true;
                }
            }
        }
        return false;
    }

    bool addShow(const Show& newShow) {
        if (count >= capacity) {
            cout << "Schedule is full!" << endl;
            return false;
        }
        if (checkOverlap(newShow)) {
            cout << "Overlap detected for " << newShow.getMovie().getTitle()
                 << " in " << newShow.getHall().getHallName() << "!" << endl;
            return false;
        }
        shows[count] = newShow;
        count++;
        return true;
    }

    void displaySchedule() const {
        cout << "--- Daily Show Schedule (" << count << " shows) ---" << endl;
        for (int i = 0; i < count; i++) {
            shows[i].showDetails();
        }
    }
};

int main() {
    //  Module 1
    Movie m1("Dune 3", 150, "Warner");
    ScreenHall h1("Hall_01_IMAX", "Platinum", 5, 6, 22.0);
    Show s1(m1, h1, 1080, 30); // 18:00 start, 30 min cleaning

    Scheduler sched;
    sched.addShow(s1);
    sched.displaySchedule();
    cout << endl;

    // Module 2
    SeatMatrix sm(h1.getRows(), h1.getCols());
    sm.displayMatrix();

    sm.lockSeat(1, 2); // C3
    sm.lockSeat(1, 3); // C4
    sm.lockSeat(1, 2); // Already locked -> suggests free seats instead of plain rejection
    sm.confirmBooking(1, 2);
    sm.confirmBooking(1, 3);

    string bookedLabels[2] = {"C3", "C4"};
    Booking b1("BK101", 1, h1.getHallClass(), bookedLabels, 2, h1.getBasePrice());
    b1.printBooking();
    cout << endl;

    // Module 3
    SnackItem popcorn("Popcorn", 8.0, 3.0, 50);
    SnackItem soda("Soda", 4.5, 1.5, 50);
    ComboDeal combo("Large Combo", popcorn, soda, 14.5);
    SnackLedger ledger;

    ledger.recordRestock(popcorn, 10);
    ledger.recordRestock(soda, 10);

    ConcessionOrder order;
    if (popcorn.checkAvailability(1) && soda.checkAvailability(1)) {
        popcorn.reduceStock(1);
        soda.reduceStock(1);
        order.addItem(combo.getComboName(), 1, combo.computeComboPrice());
        ledger.recordSale(combo.computeComboPrice());
    }
    ledger.displaySnackSummary(popcorn, soda);
    cout << endl;

    // Module 4
    LoyaltyProgram loyalty;
    loyalty.registerMember(Member(1, "Sara"));
    loyalty.addGiftCard(GiftCard("GC-100", 50.0));
    loyalty.addGiftCard(GiftCard("GC-101", 50.0));

    loyalty.addPoints(b1.getMemberId(), b1.getEarnedPoints());
    loyalty.showMemberStatus(1);
    cout << "Total Gift Card Value: $" << loyalty.getTotalGiftCardValue() << endl;
    cout << endl;

    // Module 5
    DistributorContract contract(m1.getDistributor(), 50.0);
    BoxOfficeReport report(m1.getTitle(), 20, h1.getSeatCapacity(), 440.0);
    Settlement settlement(contract, report, ledger.getSnackProfit(), loyalty.getTotalGiftCardValue());
    settlement.printSettlement();

    return 0;
}