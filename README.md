# Cinema Multiplex Ticketing & Loyalty Management System

An object-oriented C++ console application designed to manage movie screen schedules, interactive seat reservations, concession stand inventory, customer loyalty points, and studio box-office settlements.

## Core Functional Modules
Beyond the five core modules implemented in Milestone 1, the following ten modules define the broader architectural scope of the **Cinema Multiplex Ticketing & Loyalty Management System**:

1. **Movie Catalog & Metadata Management Module:** Maintains the central repository of active and upcoming films, storing titles, genres, languages, censor ratings (PG-13, R), total runtimes, and distributor agreements for validated scheduling.
2. **Dynamic Pricing & Surge Tariff Engine:** Automatically adjusts base ticket prices based on showtime demand (matinee discounts vs. prime evening rates), weekend/holiday surcharges, and auditorium categories.
3. **Ticket Cancellation & Refund Processing Module:** Validates cancellation requests against pre-show cutoff timers (e.g., 2 hours prior to screening), computes cancellation fee deductions, updates transaction logs, and releases canceled seats back to availability.
4. **Digital E-Ticket & QR Gate Validator Module:** Generates unique alphanumeric booking references upon checkout and verifies ticket authenticity at auditorium entry gates to prevent duplicate entries.
5. **Pantry Supply Chain & Low-Stock Alert Module:** Tracks raw concession inventory (corn kernels, beverage syrups, packaging cups), triggers low-stock warnings below threshold limits, and generates vendor restock orders.
6. **Promotional Voucher & Corporate Bulk Booking Module:** Validates discount promo codes, student/senior concessions, and bulk seat reservations for corporate events or school screenings, applying automated percentage discounts at checkout.
7. **Staff Shift & Role-Based Access Control (RBAC) Module:** Authenticates box-office cashiers, concession operators, and cinema managers using role-specific credentials, restricting financial settlement operations to authorized managers.
8. **Auditorium Maintenance & Equipment Health Tracker:** Logs projector lamp hours, audio calibration schedules, and damaged seat reports, blocking affected screens or seats from active scheduling until repairs are cleared.
9. **Entertainment Tax & Regulatory Compliance Module:** Computes regional entertainment duties and Goods & Services Tax (GST) separately on movie tickets and food items to produce tax-compliant itemized receipts.
10. **Waitlist & Automated Seat-Release Notification Module:** Places customers on a priority queue for sold-out screenings and notifies the next patron in line if an unpaid seat reservation expires.

## Repository Branching Rules
- Each member develops their assigned module in a separate branch (e.g., `member1-scheduler`).
- Completed modules are merged into `main` via reviewed Pull Requests.
