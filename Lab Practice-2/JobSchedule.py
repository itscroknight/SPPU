profit = [15, 27, 10, 100, 150]
jobs = ["j1", "j2", "j3", "j4", "j5"]
deadline = [2, 3, 3, 3, 4]

profitNJobs = list(zip(profit, jobs, deadline))
profitNJobs = sorted(profitNJobs, key=lambda x: x[0], reverse=True)

# Initialize slots for each day
slots = [0] * (max(deadline) + 1)

profit_total = 0
schedule = [""] * len(jobs)

for i in range(len(jobs)):
    job = profitNJobs[i]
    for j in range(job[2], 0, -1):
        if slots[j] == 0:
            schedule[i] = job[1] 
            profit_total += job[0]
            slots[j] = 1
            break
    else:
        schedule[i] = "unscheduled"

# Printing the schedule and total profit
print("Jobs scheduled:", schedule)
print("Total profit:",profit_total)
