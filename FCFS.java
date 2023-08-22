import java.util.*;

class Task {
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int processID;

    Task(int arrivalTime, int burstTime, int processID) {
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.processID = processID;
    }
}

public class Sorting {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of processes: ");
        int n = sc.nextInt();
        Task tasks[] = new Task[n];
        float avgWaitingTime = 0, avgTurnaroundTime = 0;

        for (int i = 0; i < n; i++) {
            System.out.print("Arrival time for process " + (i + 1) + ": ");
            int arrivalTime = sc.nextInt();
            System.out.print("Burst time for process " + (i + 1) + ": ");
            int burstTime = sc.nextInt();
            tasks[i] = new Task(arrivalTime, burstTime, i + 1);
        }

        Arrays.sort(tasks, Comparator.comparingInt(task -> task.arrivalTime));

        for (int i = 0; i < n; i++) {
            tasks[i].completionTime = (i == 0 ? tasks[i].arrivalTime : Math.max(tasks[i].arrivalTime, tasks[i - 1].completionTime)) + tasks[i].burstTime;
            tasks[i].turnaroundTime = tasks[i].completionTime - tasks[i].arrivalTime;
            tasks[i].waitingTime = tasks[i].turnaroundTime - tasks[i].burstTime;
            avgWaitingTime += tasks[i].waitingTime;
            avgTurnaroundTime += tasks[i].turnaroundTime;
        }

        System.out.println("\nProcessID Arrival Burst Completion Turnaround Waiting");
        for (Task task : tasks) {
            System.out.printf("%-9d%-9d%-8d%-11d%-11d%d%n",
                    task.processID, task.arrivalTime, task.burstTime, task.completionTime, task.turnaroundTime, task.waitingTime);
        }

        System.out.println("\nAverage Waiting Time: " + (avgWaitingTime / n));
        System.out.println("Average Turnaround Time: " + (avgTurnaroundTime / n));

        sc.close();
    }
}
    
