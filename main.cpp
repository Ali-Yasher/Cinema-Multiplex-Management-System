#include <iostream>
#include <string>

using namespace std;

//========================================MODULE:1===============================================

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

//=========================================MODULE:2==============================================

class Seat {
    private:
        int row;
        int col;
        string status; // "Free", "Locked", "Booked"
    
    public:
        Seat() {
            row = 0;
            col = 0;
            status = "Free";
        }
    
        Seat(int r, int c) {
            row = (r >= 0) ? r : 0;
            col = (c >= 0) ? c : 0;
            status = "Free";
        }
    
        Seat(const Seat& other) {
            row = other.row;
            col = other.col;
            status = other.status;
        }
    
        int getRow() const { return row; }
        int getCol() const { return col; }
        string getStatus() const { return status; }
    
        bool lock() {
            if (status == "Free") {
                status = "Locked";
                return true;
            }
            return false;
        }
    
        bool book() {
            if (status == "Locked" || status == "Free") {
                status = "Booked";
                return true;
            }
            return false;
        }
    
        bool release() {
            if (status == "Locked") {
                status = "Free";
                return true;
            }
            return false;
        }
    };
    
    class SeatMatrix {
    private:
        int rows;
        int cols;
        Seat** grid;
    
        void allocateGrid(int r, int c) {
            rows = (r > 0) ? r : 1;
            cols = (c > 0) ? c : 1;
            grid = new Seat*[rows];
            for (int i = 0; i < rows; i++) {
                grid[i] = new Seat[cols];
                for (int j = 0; j < cols; j++) {
                    grid[i][j] = Seat(i, j);
                }
            }
        }
    
        void freeGrid() {
            if (grid != nullptr) {
                for (int i = 0; i < rows; i++) {
                    delete[] grid[i];
                }
                delete[] grid;
                grid = nullptr;
            }
        }
    
    public:
        SeatMatrix() {
            rows = 0;
            cols = 0;
            grid = nullptr;
        }
    
        SeatMatrix(int r, int c) {
            allocateGrid(r, c);
        }
    
        SeatMatrix(const SeatMatrix& other) {
            rows = other.rows;
            cols = other.cols;
            if (other.grid != nullptr && rows > 0 && cols > 0) {
                grid = new Seat*[rows];
                for (int i = 0; i < rows; i++) {
                    grid[i] = new Seat[cols];
                    for (int j = 0; j < cols; j++) {
                        grid[i][j] = other.grid[i][j];
                    }
                }
            } else {
                grid = nullptr;
            }
        }
    
        ~SeatMatrix() {
            freeGrid();
        }
    
        int getRows() const { return rows; }
        int getCols() const { return cols; }
    
        string getSeatStatus(int r, int c) const {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                return grid[r][c].getStatus();
            }
            return "Invalid";
        }
    
        int countFreeSeats() const {
            int freeCount = 0;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (grid[i][j].getStatus() == "Free") {
                        freeCount++;
                    }
                }
            }
            return freeCount;
        }
    
        bool lockSeat(int r, int c) {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                if (grid[r][c].lock()) {
                    return true;
                }
            }
            cout << "Seat " << static_cast<char>('A' + r) << (c + 1) << " is not Free." << endl;
            suggestNearestFree(r, c, 2);
            return false;
        }
    
        bool confirmBooking(int r, int c) {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                return grid[r][c].book();
            }
            return false;
        }
    
        bool releaseSeat(int r, int c) {
            if (r >= 0 && r < rows && c >= 0 && c < cols) {
                return grid[r][c].release();
            }
            return false;
        }
    
        void suggestNearestFree(int targetRow, int targetCol, int needed) const {
            cout << "Suggested free seats: ";
            int found = 0;
            int maxDist = rows + cols;
    
            for (int dist = 0; dist <= maxDist && found < needed; dist++) {
                for (int i = 0; i < rows && found < needed; i++) {
                    for (int j = 0; j < cols && found < needed; j++) {
                        int rDiff = (i > targetRow) ? (i - targetRow) : (targetRow - i);
                        int cDiff = (j > targetCol) ? (j - targetCol) : (targetCol - j);
                        if (rDiff + cDiff == dist && grid[i][j].getStatus() == "Free") {
                            cout << static_cast<char>('A' + i) << (j + 1) << " ";
                            found++;
                        }
                    }
                }
            }
            if (found == 0) {
                cout << "None available";
            }
            cout << endl;
        }
    
        void displayMatrix() const {
            cout << "   ";
            for (int j = 0; j < cols; j++) {
                cout << " " << (j + 1) << " ";
            }
            cout << "   (. = Free, L = Locked, X = Booked)" << endl;
    
            for (int i = 0; i < rows; i++) {
                cout << " " << static_cast<char>('A' + i) << " ";
                for (int j = 0; j < cols; j++) {
                    string st = grid[i][j].getStatus();
                    char sym = '.';
                    if (st == "Locked") sym = 'L';
                    else if (st == "Booked") sym = 'X';
                    cout << "[" << sym << "]";
                }
                cout << endl;
            }
            cout << "Total Free Seats: " << countFreeSeats() << endl;
        }
    };
    
    class Booking {
    private:
        string bookingId;
        int memberId;
        string hallClass;
        string* seatLabels;
        int seatCount;
        double ticketTotal;
        int earnedPoints;
    
    public:
        Booking() {
            bookingId = "BK000";
            memberId = 0;
            hallClass = "Silver";
            seatLabels = nullptr;
            seatCount = 0;
            ticketTotal = 0.0;
            earnedPoints = 0;
        }
    
        Booking(string bId, int mId, string hClass, string labels[], int count, double unitPrice) {
            bookingId = bId;
            memberId = mId;
            hallClass = hClass;
            seatCount = (count > 0) ? count : 0;
            ticketTotal = (unitPrice >= 0.0) ? (unitPrice * seatCount) : 0.0;
    
            if (seatCount > 0 && labels != nullptr) {
                seatLabels = new string[seatCount];
                for (int i = 0; i < seatCount; i++) {
                    seatLabels[i] = labels[i];
                }
            } else {
                seatLabels = nullptr;
            }
    
            earnedPoints = calculatePointsByHallClass();
        }
    
        Booking(const Booking& other) {
            bookingId = other.bookingId;
            memberId = other.memberId;
            hallClass = other.hallClass;
            seatCount = other.seatCount;
            ticketTotal = other.ticketTotal;
            earnedPoints = other.earnedPoints;
    
            if (other.seatLabels != nullptr && seatCount > 0) {
                seatLabels = new string[seatCount];
                for (int i = 0; i < seatCount; i++) {
                    seatLabels[i] = other.seatLabels[i];
                }
            } else {
                seatLabels = nullptr;
            }
        }
    
        ~Booking() {
            delete[] seatLabels;
        }
    
        void setTicketTotal(double total) {
            if (total >= 0.0) {
                ticketTotal = total;
                earnedPoints = calculatePointsByHallClass();
            }
        }
    
        string getBookingId() const { return bookingId; }
        int getMemberId() const { return memberId; }
        string getHallClass() const { return hallClass; }
        double getTicketTotal() const { return ticketTotal; }
        int getEarnedPoints() const { return earnedPoints; }
    
        int calculatePointsByHallClass() const {
            double rate = 1.0; // Silver = 1 pt/$1
            if (hallClass == "Gold") {
                rate = 1.5;
            } else if (hallClass == "Platinum") {
                rate = 2.0;
            }
            return static_cast<int>(ticketTotal * rate);
        }
    
        void printBooking() const {
            cout << "Booking ID: " << bookingId
                 << " | Member ID: " << memberId
                 << " | Hall Class: " << hallClass
                 << " | Seats: ";
            for (int i = 0; i < seatCount; i++) {
                cout << seatLabels[i] << (i + 1 < seatCount ? ", " : "");
            }
            cout << " | Ticket Total: $" << ticketTotal
                 << " | Ticket Loyalty Points: " << earnedPoints << endl;
        }
    };

    // ==================== MODULE 4 ====================
class Member {
    private:
        int memberId;
        string name;
        int points;
        string tier;
    
        void updateTier() {
            if (points >= 150) {
                tier = "Gold";
            } else if (points >= 50) {
                tier = "Silver";
            } else {
                tier = "Bronze";
            }
        }
    
    public:
        Member() {
            memberId = 0;
            name = "Guest";
            points = 0;
            tier = "Bronze";
        }
    
        Member(int id, string n) {
            memberId = id;
            setName(n);
            points = 0;
            tier = "Bronze";
        }
    
        Member(const Member& other) {
            memberId = other.memberId;
            name = other.name;
            points = other.points;
            tier = other.tier;
        }
    
        void setName(string n) {
            if (!n.empty()) name = n;
        }
    
        int getMemberId() const { return memberId; }
        string getName() const { return name; }
        int getPoints() const { return points; }
        string getTier() const { return tier; }
    
        void addPoints(int pts) {
            if (pts > 0) {
                points += pts;
                updateTier();
            }
        }
    
        bool redeemPoints(int pts) {
            if (pts > 0 && points >= pts) {
                points -= pts;
                updateTier();
                return true;
            }
            return false;
        }
    };
    
    class GiftCard {
    private:
        string cardNumber;
        double balance;
    
    public:
        GiftCard() {
            cardNumber = "GC-000";
            balance = 0.0;
        }
    
        GiftCard(string num, double bal) {
            cardNumber = num;
            setBalance(bal);
        }
    
        GiftCard(const GiftCard& other) {
            cardNumber = other.cardNumber;
            balance = other.balance;
        }
    
        void setBalance(double bal) {
            if (bal >= 0.0) balance = bal;
        }
    
        string getCardNumber() const { return cardNumber; }
        double getBalance() const { return balance; }
    
        void recharge(double amount) {
            if (amount > 0.0) balance += amount;
        }
    
        bool deduct(double amount) {
            if (amount > 0.0 && balance >= amount) {
                balance -= amount;
                return true;
            }
            return false;
        }
    };
    
    class LoyaltyProgram {
    private:
        Member* members;
        int memberCount;
        int memberCap;
    
        GiftCard* cards;
        int cardCount;
        int cardCap;
    
    public:
        LoyaltyProgram() {
            memberCap = 20;
            memberCount = 0;
            members = new Member[memberCap];
    
            cardCap = 20;
            cardCount = 0;
            cards = new GiftCard[cardCap];
        }
    
        LoyaltyProgram(const LoyaltyProgram& other) {
            memberCap = other.memberCap;
            memberCount = other.memberCount;
            members = new Member[memberCap];
            for (int i = 0; i < memberCount; i++) {
                members[i] = other.members[i];
            }
    
            cardCap = other.cardCap;
            cardCount = other.cardCount;
            cards = new GiftCard[cardCap];
            for (int i = 0; i < cardCount; i++) {
                cards[i] = other.cards[i];
            }
        }
    
        ~LoyaltyProgram() {
            delete[] members;
            delete[] cards;
        }
    
        int getMemberCount() const { return memberCount; }
    
        bool registerMember(const Member& m) {
            if (memberCount < memberCap) {
                members[memberCount] = m;
                memberCount++;
                return true;
            }
            return false;
        }
    
        bool addGiftCard(const GiftCard& gc) {
            if (cardCount < cardCap) {
                cards[cardCount] = gc;
                cardCount++;
                return true;
            }
            return false;
        }
    
        bool addPoints(int memberId, int pts) {
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getMemberId() == memberId) {
                    members[i].addPoints(pts);
                    return true;
                }
            }
            return false;
        }
    
        bool redeemFreeTicket(int memberId, int costPoints = 100) {
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getMemberId() == memberId) {
                    return members[i].redeemPoints(costPoints);
                }
            }
            return false;
        }
    
        double getTotalGiftCardValue() const {
            double total = 0.0;
            for (int i = 0; i < cardCount; i++) {
                total += cards[i].getBalance();
            }
            return total;
        }
    
        void showMemberStatus(int memberId) const {
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getMemberId() == memberId) {
                    cout << "Member [" << members[i].getMemberId() << "] " << members[i].getName()
                         << " | Points: " << members[i].getPoints()
                         << " | Tier: " << members[i].getTier() << endl;
                    return;
                }
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