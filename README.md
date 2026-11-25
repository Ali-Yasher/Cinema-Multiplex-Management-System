# Cinema Multiplex Ticketing & Loyalty Management System

An object-oriented C++ console application designed to manage movie screen schedules, interactive seat reservations, concession stand inventory, customer loyalty points, and studio box-office settlements.

## Core Functional Modules
The application is divided into five core functional modules, each engineered to handle a specific operational domain of a modern movie theater:

### 1. Showtime & Screen Scheduler
* **Owner:** Ali Yasher
* **Core Responsibility:** Manages physical theater halls, movie catalogs, and screening schedules while preventing scheduling conflicts.
* **Key Features:**
  * Configures theater halls with specific screen types (e.g., Standard, IMAX, VIP) and seating capacities.
  * Registers movies along with their exact runtimes.
  * Automatically enforces a mandatory **cleaning & turnover gap** between consecutive screenings in the same hall to prevent overlapping shows.
* **Primary Data Managed:** Hall types, seating capacities, movie runtimes, show start times, and cleaning buffer durations (in minutes).

### 2. Seat Selection Engine
* **Owner:** M. Afnan
* **Core Responsibility:** Handles real-time visual seating layouts and manages seat reservation states during the booking lifecycle.
* **Key Features:**
  * Dynamically renders a 2D seat matrix mapped to each hall's specific capacity and layout.
  * Implements state-machine transitions for seats: **Free** (available for selection), **Locked** (temporarily held during checkout), and **Booked** (confirmed purchase).
  * Automatically releases locked seats if a transaction times out or is canceled.
* **Primary Data Managed:** 2D seat matrices, row/column coordinates, and real-time seat states (`Free`, `Locked`, `Booked`).

### 3. Concessions & Candy Bar POS
* **Owner:** Wafa Saqib
* **Core Responsibility:** Operates the Point-of-Sale (POS) system for food, beverages, and snacks alongside live inventory tracking.
* **Key Features:**
  * Processes snack and combo orders at the counter or alongside ticket checkouts.
  * Automatically deducts sold quantities from pantry inventory in real time to prevent overselling.
  * Tracks itemized order lines for accurate receipt generation and stock auditing.
* **Primary Data Managed:** Item names, unit prices, current pantry stock levels, and itemized order lines.

### 4. Loyalty & Gift Card System
* **Owner:** Asad Ali Raza
* **Core Responsibility:** Drives customer retention through a points-based rewards program, membership tiers, and gift card redemptions.
* **Key Features:**
  * Calculates and awards loyalty points automatically based on dollar spend across tickets and concessions.
  * Tracks customer membership tiers (e.g., Silver, Gold, Platinum) based on cumulative activity.
  * Allows members to redeem accumulated points or gift card balances directly toward movie tickets.
* **Primary Data Managed:** Member profiles/names, point balances, loyalty tier statuses, and redemption histories.

### 5. Settlement & Analytics
* **Owner:** Alsihba Hanif
* **Core Responsibility:** Aggregates operational and financial data to calculate distributor revenue splits and theater performance metrics.
* **Key Features:**
  * Computes gross box office revenue and executes automated revenue-sharing calculations (e.g., 50/50 split between the theater and film distributors).
  * Calculates hall occupancy percentages by comparing total tickets sold against available hall capacity per showtime and across date ranges.
* **Primary Data Managed:** Gross/net revenue figures, revenue split percentages, total seats sold, and total available capacity.

---

## Team & Module Ownership

| # | Owner | Module | Core Job | Primary Data Entities |
| :- | :--- | :--- | :--- | :--- |
| **1** | **Ali Yasher** | Showtime & Screen Scheduler | Creates halls, movies, and shows; prevents overlaps via cleaning gaps. | Hall type, capacity, runtime, start time, cleaning minutes |
| **2** | **M. Afnan** | Seat Selection Engine | Renders seat grids; locks, books, or releases seats. | Seat matrix, seat state (`Free` / `Locked` / `Booked`) |
| **3** | **Wafa Saqib** | Concessions & Candy Bar POS | Processes snack sales and deducts from pantry inventory. | Item name, price, stock, order lines |
| **4** | **Asad Ali Raza** | Loyalty & Gift Card | Awards points per dollar, tracks tiers, and redeems points for tickets. | Member name, points, tier |
| **5** | **Alsihba Hanif** | Settlement & Analytics | Splits box office revenue and calculates occupancy percentages. | Revenue, split %, seats sold vs. total capacity |

---

## End-to-End Operational Workflow

1. **Scheduling:** A hall and movie are registered in the **Showtime & Screen Scheduler**, establishing a valid, conflict-free screening slot.
2. **Ticketing & Locking:** A customer selects a showtime; the **Seat Selection Engine** displays the live seat matrix and temporarily **Locks** the chosen seats.
3. **Upselling & Loyalty:** During checkout, the customer adds snacks via the **Concessions POS** (deducting pantry stock) and applies their **Loyalty** account to earn or redeem points.
4. **Confirmation:** Upon payment, locked seats transition to **Booked**, and points are credited to the member's profile.
5. **Reporting:** At the end of the screening or business day, **Settlement & Analytics** calculates the hall's occupancy rate and divides ticket revenue according to the configured split percentage.
