import tkinter as tk
from tkinter import ttk, messagebox
from PIL import Image, ImageTk  # Importing Pillow for image resizing
from datetime import datetime, timedelta
import time
import threading
import winsound

def pomodoroFunction(root):
    root.withdraw()
    class PomodoroTimer:
        def __init__(self, work_duration, short_break, long_break):
            self.work_duration = work_duration
            self.short_break = short_break
            self.long_break = long_break
            self.reset_flag = False
            self.stop_flag = False
            self.running = False
            self.paused = False
            self.remaining_time = 0
            self.timer_thread = None
            self.current_time = ""
            self.ringtone_playing = False
            self.ringtone_thread = None

        def play_ringtone(self):
            self.ringtone_playing = True
            while self.ringtone_playing:
                winsound.Beep(480, 500)  # 480 Hz frequency, 500 ms duration
                time.sleep(0.5)  # Small delay to mimic a ringtone effect

        def stop_ringtone(self):
            self.ringtone_playing = False
            if self.ringtone_thread and self.ringtone_thread.is_alive():
                self.ringtone_thread.join()  # Ensure ringtone thread finishes

        def pomodoro_timer(self, duration, phase):
            self.running = True
            self.paused = False
            if self.remaining_time == 0:
                self.update_display(f"{phase} phase started.")
                self.remaining_time = duration * 60  # Set remaining time in seconds

            self.countdown(phase)

        def countdown(self, phase):
            while self.remaining_time > 0:
                if self.reset_flag:
                    self.remaining_time = 0
                    self.stop_ringtone() 
                    self.update_display(f"{phase} phase reset.")
                    return

                if self.stop_flag:  # If stop button is clicked, pause the timer
                    self.paused = True
                    self.update_display(f"Paused at {self.format_time(self.remaining_time)}")
                    return  # Pause the countdown

                mins, secs = divmod(self.remaining_time, 60)
                timer = f"{mins:02d}:{secs:02d}"
                self.update_display(timer)
                time.sleep(1)
                self.remaining_time -= 1  # Decrement remaining time by 1 second

            # If timer finishes and reset wasn't triggered
            if not self.reset_flag:
                self.update_display(f"{phase} phase complete!")
                self.ringtone_thread = threading.Thread(target=self.play_ringtone)
                self.ringtone_thread.start()
            self.running = False
            self.remaining_time = 0

        def stop_timer(self):
            self.stop_ringtone()  # Stop the ringtone
            self.stop_flag = True
            if self.remaining_time > 0:
                self.paused = True  # Set paused to True when the timer is stopped
                self.running = False  # Set running to False when the timer is stopped
                self.update_display(f"Paused at {self.format_time(self.remaining_time)}")

        def continue_timer(self):
            if self.paused and self.remaining_time > 0:
                if not self.running:
                    # Reset stop_flag and start the countdown
                    self.stop_flag = False
                    self.paused = False
                    self.running = True

                    # Continue the countdown in the same thread, do not start a new thread
                    self.timer_thread = threading.Thread(target=self.countdown, args=("Continue",))  # Continue countdown from where it stopped
                    self.timer_thread.start()
                    self.update_display(f"Resumed at {self.format_time(self.remaining_time)}")
                else:
                    # If already running, prevent starting the countdown again
                    if self.timer_thread and self.timer_thread.is_alive():
                        self.update_display("Timer already running.")
                        return
            else:
                # Show a message if the timer is not paused or has no remaining time
                self.update_display("Timer cannot continue, ensure it's paused and has remaining time.")

        def reset_timer(self):
            self.stop_ringtone()  # Stop the ringtone if it's playing
            self.reset_flag = True
            self.stop_flag = False
            self.paused = False
            self.remaining_time = 0
            self.update_display("Timer reset")

        def update_display(self, text):
            self.current_time = text
            if app:
                app.update_timer_display(text)

        def format_time(self, seconds):
            mins, secs = divmod(seconds, 60)
            return f"{mins:02d}:{secs:02d}"

    class TimerApp:
        def __init__(self, timer):
            self.timer = timer
            self.root = tk.Tk()
            self.root.title("Pomodoro Timer")
            self.root.resizable(False, False)
            self.root.title("Pomodoro Timer")
            self.root.protocol("WM_DELETE_WINDOW", self.close_app)

            self.timer_label = tk.Label(self.root, text="00:00", font=("Helvetica", 48))
            self.timer_label.pack(pady=20)

            self.config_frame = tk.Frame(self.root)
            self.config_frame.pack(pady=10)

            tk.Label(self.config_frame, text="Work (min):").grid(row=0, column=0)
            self.work_entry = tk.Entry(self.config_frame, width=5)
            self.work_entry.insert(0, str(self.timer.work_duration))
            self.work_entry.grid(row=0, column=1)

            tk.Label(self.config_frame, text="Short Break (min):").grid(row=1, column=0)
            self.short_break_entry = tk.Entry(self.config_frame, width=5)
            self.short_break_entry.insert(0, str(self.timer.short_break))
            self.short_break_entry.grid(row=1, column=1)

            tk.Label(self.config_frame, text="Long Break (min):").grid(row=2, column=0)
            self.long_break_entry = tk.Entry(self.config_frame, width=5)
            self.long_break_entry.insert(0, str(self.timer.long_break))
            self.long_break_entry.grid(row=2, column=1)

            self.apply_button = tk.Button(self.config_frame, text="Apply", command=self.update_config)
            self.apply_button.grid(row=3, columnspan=2, pady=5)

            self.start_work_button = tk.Button(self.root, text="Start Work", command=self.start_work)
            self.start_work_button.pack(side="left", padx=10)

            self.start_short_break_button = tk.Button(self.root, text="Short Break", command=self.start_short_break, state="disabled")
            self.start_short_break_button.pack(side="left", padx=10)

            self.start_long_break_button = tk.Button(self.root, text="Long Break", command=self.start_long_break, state="disabled")
            self.start_long_break_button.pack(side="left", padx=10)

            self.stop_button = tk.Button(self.root, text="Stop", command=self.stop_timer)
            self.stop_button.pack(side="left", padx=10)

            self.continue_button = tk.Button(self.root, text="Continue", command=self.continue_timer)
            self.continue_button.pack(side="left", padx=10)

            self.reset_button = tk.Button(self.root, text="Reset", command=self.reset_timer)
            self.reset_button.pack(side="left", padx=10)

        def close_app(self):
            root.deiconify()  # Show the main window
            self.root.destroy()  # Close the PomodoroTimer window

        def update_config(self):
            try:
                # Get the input values and strip any leading/trailing spaces
                work_duration = self.work_entry.get().strip()
                short_break = self.short_break_entry.get().strip()
                long_break = self.long_break_entry.get().strip()

                # Check if the inputs are numeric (including negative numbers)
                if not work_duration.lstrip("-").isdigit() or not short_break.lstrip("-").isdigit() or not long_break.lstrip("-").isdigit():
                    raise ValueError("Only digits are allowed.")

                 # Convert the inputs to integers
                work_duration = int(self.work_entry.get())
                short_break = int(self.short_break_entry.get())
                long_break = int(self.long_break_entry.get())

                if work_duration <= 0 or short_break <= 0 or long_break <= 0:
                    raise ValueError("Duration values must be greater than zero.")

                self.timer.work_duration = work_duration
                self.timer.short_break = short_break
                self.timer.long_break = long_break
                self.update_timer_display("Configurations updated!")

            except ValueError as e:
                self.update_timer_display(f"Error: {e}")

        def start_work(self):
            self.timer.stop_ringtone()  # Call stop_ringtone on the PomodoroTimer instance
            if not self.timer.running:
                self.timer.reset_flag = False
                self.timer.stop_flag = False
                self.timer.timer_thread = threading.Thread(target=self.timer.pomodoro_timer, args=(self.timer.work_duration, "Work"))
                self.timer.timer_thread.start()
                self.start_short_break_button.config(state="normal")
                self.start_long_break_button.config(state="normal")
            else:
                self.update_timer_display("Timer is already running!")

        def start_short_break(self):
            self.timer.stop_ringtone()  # Call stop_ringtone on the PomodoroTimer instance
            if not self.timer.running:
                self.timer.reset_flag = False
                self.timer.stop_flag = False
                self.timer.timer_thread = threading.Thread(target=self.timer.pomodoro_timer, args=(self.timer.short_break, "Short Break"))
                self.timer.timer_thread.start()
            else:
                self.update_timer_display("Timer is already running!")

        def start_long_break(self):
            self.timer.stop_ringtone()  # Call stop_ringtone on the PomodoroTimer instance
            if not self.timer.running:
                self.timer.reset_flag = False
                self.timer.stop_flag = False
                self.timer.timer_thread = threading.Thread(target=self.timer.pomodoro_timer, args=(self.timer.long_break, "Long Break"))
                self.timer.timer_thread.start()
            else:
                self.update_timer_display("Timer is already running!")

        def stop_timer(self):
            self.timer.stop_ringtone()  # Call stop_ringtone on the PomodoroTimer instance
            self.timer.stop_timer()

        def continue_timer(self):
            self.timer.continue_timer()

        def reset_timer(self):
            self.timer.stop_ringtone()  # Call stop_ringtone on the PomodoroTimer instance
            self.timer.reset_timer()
            self.start_short_break_button.config(state="disabled")
            self.start_long_break_button.config(state="disabled")

        def update_timer_display(self, text):
            self.timer_label.config(text=text)

        def run(self):
            self.root.mainloop()


    # Example usage:
    if __name__ == "__main__":
        timer = PomodoroTimer(work_duration=25, short_break=5, long_break=15)
        app = TimerApp(timer)
        app.run()

def alarmClockFunction():
    root.withdraw() 
    class AlarmClockApp:
        def __init__(self, root):
            self.alarms = []  # Store alarms

            self.root = root
            self.root.title("Online Alarm Clock")
            self.root.geometry("400x735")
            self.root.resizable(False, False)
            self.root.configure(bg = "lightblue")  # Set background color of the window
        
            self.root.protocol("WM_DELETE_WINDOW", self.on_close)
            # Header
            tk.Label(root, text = "Online Alarm Clock", font = ("Roboto", 20), bg = "lightblue", fg = "darkblue").pack(pady = 10)

            # Current day and time display
            self.current_day_label = tk.Label(root, text = "", font = ("Times New Roman", 16), bg = "darkblue", fg = "lightblue")
            self.current_day_label.pack(pady = 5)

            self.current_time_label = tk.Label(root, text = "", font = ("Times New Roman", 16), bg = "darkblue", fg = "lightblue")
            self.current_time_label.pack(pady = 5)

            self.update_time()  # Start updating time

            # Add alarm section
            self.setup_add_alarm_section()

            # Active alarms section
            self.setup_alarm_list_section()

        def on_close(self):
            root.deiconify()  # Show the main window
            self.root.destroy()  # Close the AlarmClockApp window
            
        def update_time(self):
            # Get current date and time
            now = datetime.now()
    
            # Extract components
            day_name = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
            month_name = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    
            day_of_week = day_name[now.weekday()]  # Get the day name
            month = month_name[now.month - 1]      # Get the month name
            day = now.day                          # Get day of the month
            year = now.year                        # Get year
            hour = now.hour                        # Get hour (24-hour format)
            minute = now.minute                    # Get minutes
            second = now.second                    # Get seconds

            # Convert 24-hour format to 12-hour format
            if hour < 12:
                period = "AM"
            else:
                period = "PM"

            if hour > 12:
                hour = hour - 12

            if hour == 0:
                hour = 12  # Handle midnight as 12:00 AM

            # Formatted strings
            date_text = f"{day} {month} {year} ({day_of_week})"
            time_text = f"{hour:02}:{minute:02}:{second:02} {period}"

            # Update labels
            self.current_day_label.config(text = date_text)
            self.current_time_label.config(text = time_text)
            self.root.after(1000, self.update_time)

        def setup_add_alarm_section(self):
            frame = tk.Frame(self.root, bg = "lightblue", padx = 10, pady = 10)
            frame.pack(pady = 10)

            tk.Label(frame, text = "Set Alarm Time", font = ("Arial", 11), bg = "lightblue", fg = "darkblue").grid(row = 0, column = 0, columnspan = 3, pady = 5)

            hours = [f"{i:02}" for i in range(1, 13)]
            minutes = [f"{i:02}" for i in range(60)]
            repeat_options = ["Once", "Every Monday", "Every Tuesday", "Every Wednesday",
                              "Every Thursday", "Every Friday", "Every Saturday", "Every Sunday", "Every Day"]
            snooze_options = ["5", "10", "15"]

            self.hour_combobox = ttk.Combobox(frame, values = hours, state = "readonly", width = 5)
            self.minute_combobox = ttk.Combobox(frame, values = minutes, state = "readonly", width = 5)
            self.period_combobox = ttk.Combobox(frame, values = ["AM", "PM"], state = "readonly", width = 7)

            self.hour_combobox.set("HH")
            self.minute_combobox.set("MM")
            self.period_combobox.set("AM/PM")

            self.hour_combobox.grid(row = 1, column = 0, padx = 5)
            self.minute_combobox.grid(row = 1, column = 1, padx = 5)
            self.period_combobox.grid(row = 1, column = 2, padx = 5)
        
            tk.Label(frame, text = "Snooze(Minutes):", bg = "lightblue", fg = "darkblue").grid(row = 2, column = 0, columnspan = 3, pady = 5)
            self.snooze_combobox = ttk.Combobox(frame, values = snooze_options, state = "readonly", width = 10)
            self.snooze_combobox.set("5")
            self.snooze_combobox.grid(row = 3, column = 0, columnspan = 3, pady = 5)

            tk.Label(frame, text = "Alarm Name:", bg = "lightblue", fg = "darkblue").grid(row = 4, column = 0, columnspan = 3, pady = 5)
            self.alarm_name_entry = ttk.Entry(frame, width = 20)
            self.alarm_name_entry.grid(row = 5, column = 0, columnspan = 3, pady = 5)

            tk.Label(frame, text = "Repeat:", bg = "lightblue", fg = "darkblue").grid(row = 6, column = 0, columnspan = 3, pady = 5)
            self.repeat_combobox = ttk.Combobox(frame, values = repeat_options, state = "readonly", width = 20)
            self.repeat_combobox.set("Once")
            self.repeat_combobox.grid(row = 7, column = 0, columnspan = 3, pady = 5)

            tk.Button(frame, text = "Add Alarm", command = self.add_alarm, bg = "darkblue", fg = "white").grid(row = 8, column = 0, columnspan = 3, pady = 10)

        def setup_alarm_list_section(self):
            frame = tk.Frame(self.root, bg = "lightblue")
            frame.pack(padx=10, pady=10)

            tk.Label(frame, text = "Active Alarms:", font = ("Arial", 12), bg = "lightblue", fg = "darkblue").pack(anchor= "w",padx = 4, pady = 5)

            self.alarm_listbox = tk.Listbox(frame, height = 10, width = 70, bg = "snow")
            self.alarm_listbox.pack(padx = 5, pady = 5)

            tk.Button(frame, text="Delete Alarm", command = self.delete_alarm, bg = "darkblue", fg = "white").pack(pady=10)

        def add_alarm(self):
            try:
                hour_input = self.hour_combobox.get()
                minute_input = self.minute_combobox.get()
                period_input = self.period_combobox.get()
                snooze_input = self.snooze_combobox.get()
                alarm_name = self.alarm_name_entry.get()
                repeat_type = self.repeat_combobox.get()

                if hour_input == "HH" or minute_input == "MM" or period_input == "AM/PM":
                   messagebox.showerror("Error", "Please select a valid hour, minute, and period.")
                   return
            

                hour = int(hour_input)
                minute = int(minute_input)
                snooze_duration = int(snooze_input)

                if period_input == "PM" and hour != 12:
                   hour += 12
                if period_input == "AM" and hour == 12:
                   hour = 0

                now = datetime.now()
                alarm_time = datetime(now.year, now.month, now.day, hour, minute, 0, 0)

                # Adjust for alarms set for the next day
                if alarm_time < now:
                    alarm_time += timedelta(days = 1)

                for alarm in self.alarms:
                    if alarm["time"] == alarm_time and alarm["repeat"] == repeat_type:
                        messagebox.showerror("Error", "An alarm is already set for this time.")
                        return

                alarm_hour = alarm_time.hour
                alarm_minute = alarm_time.minute

                if alarm_hour == 0:
                    formatted_hour = 12
                    period = "AM"
                elif alarm_hour < 12:
                    formatted_hour = alarm_hour
                    period = "AM"
                elif alarm_hour == 12:
                    formatted_hour = 12
                    period = "PM"
                else:
                    formatted_hour = alarm_hour - 12
                    period = "PM"

                # Format minute to always show two digits
                formatted_minute = f"{alarm_minute:02}"

                # Combine to get the formatted time
                formatted_alarm_time = f"{formatted_hour}:{formatted_minute} {period}"

                alarm = {"time": alarm_time, "name": alarm_name, "repeat": repeat_type, "is_ringing": False, "cancel": False, "snooze_duration": snooze_duration}
                self.alarms.append(alarm)
                self.alarm_listbox.insert(tk.END, f"{alarm_name} - {formatted_alarm_time} ({repeat_type}, Snooze: {snooze_duration} min)")
                threading.Thread(target = self.check_alarm, args = (alarm,), daemon = True).start()
                messagebox.showinfo("Alarm Added", f"Alarm '{alarm_name}' set for {formatted_alarm_time} ({repeat_type})")
            except ValueError:
                messagebox.showerror("Error", "Please select a valid hour and minute.")
        

        def delete_alarm(self):
            try:
                selected_index = self.alarm_listbox.curselection()
                if not selected_index:
                    messagebox.showerror("Error","No alarm selected.")
                    return
                selected_index = selected_index[0]
                self.alarms[selected_index]["cancel"] = True
                self.alarms.pop(selected_index)
                self.alarm_listbox.delete(selected_index)
                messagebox.showinfo("Alarm Deleted", "Alarm deleted successfully.")
            except Exception:
                messagebox.showerror("Error", "No alarm selected.")

        def check_alarm(self, alarm):
            while not alarm["is_ringing"] and not alarm["cancel"]:
                now = datetime.now()

                # Check "Once" repeat type
                if alarm["repeat"] == "Once" and now >= alarm["time"]:
                    alarm["is_ringing"] = True

                # Check "Every Day" repeat type (same time every day)
                elif alarm["repeat"] == "Every Day" and now.hour == alarm["time"].hour and now.minute == alarm["time"].minute:
                    alarm["is_ringing"] = True

                # Check for "Every <Day of the Week>" repeat type
                elif alarm["repeat"].startswith("Every"):
                    day_of_week = now.weekday()  # 0 for Monday, 6 for Sunday
            
                    # Map the repeat string to corresponding weekday numbers
                    weekday_dict = {
                        "Monday": 0,
                        "Tuesday": 1,
                        "Wednesday": 2,
                        "Thursday": 3,
                        "Friday": 4,
                        "Saturday": 5,
                        "Sunday": 6,
                    }
            
                    # Extract the day name from the repeat string
                    repeat_day = alarm["repeat"].split()[-1]
            
                    # Check if today matches the repeat day
                    if weekday_dict.get(repeat_day) == day_of_week:
                        if now.hour == alarm["time"].hour and now.minute == alarm["time"].minute:
                            alarm["is_ringing"] = True


                if alarm["is_ringing"]:
                    self.ring_alarm(alarm)
                time.sleep(1)

        def ring_alarm(self, alarm):
            threading.Thread(target=self.play_sound, args=(alarm,), daemon=True).start()
            self.show_alarm_popup(alarm)

        def play_sound(self, alarm):
            while alarm["is_ringing"]:
                winsound.Beep(2500, 1000)
                time.sleep(1)

        def show_alarm_popup(self, alarm):
            def stop():
                alarm["is_ringing"] = False
                alarm["cancel"] = True
                winsound.PlaySound(None, winsound.SND_ASYNC)
                if alarm["repeat"] == "Once":
                    self.alarms.remove(alarm)
                    self.update_alarm_list()
                dialog.destroy()
                self.root.attributes("-disabled", False)  # Re-enable the AlarmClockApp window
                
            def snooze():
                alarm["is_ringing"] = False
                winsound.PlaySound(None, winsound.SND_ASYNC)
                alarm["time"] += timedelta(minutes=alarm["snooze_duration"])
                threading.Thread(target=self.check_alarm, args=(alarm,), daemon=True).start()
                dialog.destroy()
                self.root.attributes("-disabled", False)  # Re-enable the AlarmClockApp window
                messagebox.showinfo("Snooze", f"The alarm '{alarm['name']}' has been snoozed for {alarm['snooze_duration']} minutes.")

            # Disable the AlarmClockApp window
            self.root.attributes("-disabled", True)
    
            dialog = tk.Toplevel(self.root)
            dialog.title("Alarm")
            dialog.geometry("300x150")
            dialog.resizable(False, False)
            dialog.protocol("WM_DELETE_WINDOW", stop)
            dialog.configure(bg = "lightblue")

            tk.Label(dialog, text=f"Alarm '{alarm['name']}' is ringing!", font = ("Arial", 14), bg = "lightblue", fg = "darkblue").pack(pady = 10)
            tk.Button(dialog, text="Stop", command = stop, bg = "darkblue", fg = "lightblue").pack(side = tk.LEFT, padx = 10)
            tk.Button(dialog, text="Snooze", command = snooze, bg = "darkblue", fg = "lightblue").pack(side = tk.RIGHT, padx = 10)

        def update_alarm_list(self):
            self.alarm_listbox.delete(0, tk.END)
            for alarm in self.alarms:
                # Get repeat type and alarm time
                repeat_type = alarm["repeat"]
                alarm_time = alarm["time"]
        
                # Manually calculate the hour and minute
                hour = alarm_time.hour
                minute = alarm_time.minute
        
                # Determine AM/PM period
                if hour < 12:
                    period = "AM"
                else:
                    period = "PM"
        
                if hour == 0:
                    hour = 12  # Handle midnight as 12:xx AM
                elif hour > 12:
                    hour -= 12  # Convert from 24-hour format to 12-hour format
        
                # Ensure two digits for minute
                minute = f"{minute:02}"

                # Create the formatted alarm time string manually
                formatted_alarm_time = f"{hour}:{minute} {period}"

                # Insert the alarm details into the listbox
                self.alarm_listbox.insert(tk.END, f"{alarm['name']} - {formatted_alarm_time} ({repeat_type})")

    alarm_root = tk.Toplevel()
    AlarmClockApp(alarm_root)

def timerFunction():
    root.withdraw() 
    class TimerApp:
        def __init__(self, root):
            self.hour = 0
            self.minute = 0
            self.second = 0
            self.paused = False  # Global flag to track if the timer is paused
            #self.time_label = None  # Global variable for time label
            
            self.root = root
            self.root.title("Timer")
            self.root.geometry("450x380")
            self.root.resizable(False, False)
            self.root.configure(bg = "sandy brown")  # Set background color of the window
        
            self.root.protocol("WM_DELETE_WINDOW", self.on_close)
            # Header
            tk.Label(root, text = "Timer", font = ("Roboto", 20), bg = "sandy brown", fg = "black").pack(pady = 10)

            frame = tk.Frame(self.root, bg = "sandy brown", padx = 10, pady = 10)
            frame.pack(pady = 10)

            # Timer buttons for changing hours, minutes, and seconds
            self.time = tk.Button(frame, text="-10h", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MTH).grid(row=0, column=1)
            self.time = tk.Button(frame, text="-1h", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MOH).grid(row=0, column=2)
            self.time = tk.Button(frame, text="-10m", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MTM).grid(row=0, column=4)
            self.time = tk.Button(frame, text="-1m", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MOM).grid(row=0, column=5)
            self.time = tk.Button(frame, text="-10s", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MTS).grid(row=0, column=7)
            self.time = tk.Button(frame, text="-1s", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.MOS).grid(row=0, column=8)

            self.time = tk.Button(frame, text="+10h", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.PTH).grid(row=4, column=1)
            self.time = tk.Button(frame, text="+1h", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.POH).grid(row=4, column=2)
            self.time = tk.Button(frame, text="+10m", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.PTM).grid(row=4, column=4)
            self.time = tk.Button(frame, text="+1m", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.POM).grid(row=4, column=5)
            self.time = tk.Button(frame, text="+10s", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.PTS).grid(row=4, column=7)
            self.time = tk.Button(frame, text="+1s", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.POS).grid(row=4, column=8)
            
            self.time_label = tk.Label(frame, text="{:02d}:{:02d}:{:02d}".format(0, 0, 0), font=("Arial Black", 40), bg = "snow", fg = "black")
            self.time_label.grid(row=2, column=1, columnspan=8)
            
            self.name = tk.Label(frame, text="Name: ", bg = "sandy brown", fg = "black").grid(row=6, column=2, columnspan=2)
     
            self.name_entry = tk.Entry(frame)
            self.name_entry.grid(row=6, column=4, columnspan=2)

            self.add_btn = tk.Button(frame, text="Start", font=("Arial", 10), bg = "LightGoldenrod3", fg = "black", command=self.start)
            self.add_btn.grid(row=8, column=4, columnspan=2)

            self.space = tk.Label(frame, text="", bg = "sandy brown").grid(row=1)
            self.space = tk.Label(frame, text="", bg = "sandy brown").grid(row=3)
            self.space = tk.Label(frame, text="", bg = "sandy brown").grid(row=5)
            self.space = tk.Label(frame, text="", bg = "sandy brown").grid(row=7)

        def MTH(self):
            self.hour -= 10
            self.hour = max(0, min(self.hour, 99))
            self.update_time_display()

        def MOH(self):
            self.hour -= 1
            self.hour = max(0, min(self.hour, 99))
            self.update_time_display()

        def MTM(self):
            self.minute -= 10
            self.minute = max(0, min(self.minute, 59))
            self.update_time_display()

        def MOM(self):
            self.minute -= 1
            self.minute = max(0, min(self.minute, 59))
            self.update_time_display()

        def MTS(self):
            self.second -= 10
            self.second = max(0, min(self.second, 59))
            self.update_time_display()

        def MOS(self):
            self.second -= 1
            self.second = max(0, min(self.second, 59))
            self.update_time_display()

        def PTH(self):
            self.hour += 10
            self.hour = max(0, min(self.hour, 99))
            self.update_time_display()

        def POH(self):
            self.hour += 1
            self.hour = max(0, min(self.hour, 99))
            self.update_time_display()

        def PTM(self):
            self.minute += 10
            self.minute = max(0, min(self.minute, 59))
            self.update_time_display()

        def POM(self):
            self.minute += 1
            self.minute = max(0, min(self.minute, 59))
            self.update_time_display()

        def PTS(self):
            self.second += 10
            self.second = max(0, min(self.second, 59))
            self.update_time_display()

        def POS(self):
            self.second += 1
            self.second = max(0, min(self.second, 59))
            self.update_time_display()

            
        def update_time_display(self):
            self.time_label.config(text="{:02d}:{:02d}:{:02d}".format(self.hour, self.minute, self.second))
            #self.root.after(1000, self.update_time_display)

        def start(self):
            self.entry_value = self.name_entry.get()  # Get the value from the entry widget
            global h, m, s
            h = self.hour
            m = self.minute
            s = self.second
            self.paused = False  # Reset paused flag when starting a new timer
                  
            if h + m + s == 0:
                def ok():
                    self.root.attributes("-disabled", False)
                    Warning.destroy()
                Warning = tk.Toplevel(root)  # Create warning window
                Warning.geometry("250x100")
                Warning.resizable(False, False)
                Warning.title("Warning!")
                Warning.protocol("WM_DELETE_WINDOW", ok)
                self.root.attributes("-disabled", True)
                caution = tk.Label(Warning, text="Timer cannot be 0").place(relx=0.5, rely=0.3, anchor="center")
                ok = tk.Button(Warning, text="Ok", command=ok).place(relx=0.5, rely=0.6, anchor="center")

            else:
                self.root.attributes("-disabled", True)
                timer = tk.Toplevel(root)  # Create timer window
                timer.geometry("520x300")
                timer.minsize(520, 300)
                timer.title("Timer")
                timer.configure(bg = "LightSkyBlue1")
                time_name = tk.Label(timer, text=self.entry_value, font=("Arial", 40), bg = "LightSkyBlue1").place(relx=0.5, rely=0.1, anchor="center")

                time_label2 = tk.Label(timer, text="{:02d}:{:02d}:{:02d}".format(h, m, s), font=("Arial Black", 80), bg = "LightSkyBlue1")
                time_label2.place(relx=0.5, rely=0.5, anchor="center")
 
                def timer_count():
                    global h, m, s
                    if self.paused:
                        return  # Do not continue the countdown if paused

                    if h + m + s > 0:
                        if s == 0 and m > 0:
                            m -= 1
                            s += 59
                            time_label2.config(text="{:02d}:{:02d}:{:02d}".format(h, m, s))
                            root.after(1000, timer_count)
                        elif s == 0 and m == 0:
                            h -= 1
                            m += 59
                            s += 59
                            time_label2.config(text="{:02d}:{:02d}:{:02d}".format(h, m, s))
                            root.after(1000, timer_count)
                        else:
                            s -= 1
                            time_label2.config(text="{:02d}:{:02d}:{:02d}".format(h, m, s))
                            root.after(1000, timer_count)
                    else:
                        def cont():
                            global h, m, s
                            h = self.hour
                            m = self.minute
                            s = self.second
                            time_up.destroy()
                            timer.deiconify()
                            time_label2.config(text="{:02d}:{:02d}:{:02d}".format(h, m, s))
                            root.after(1000, timer_count)

                        def end():
                            self.root.attributes("-disabled", False)
                            time_up.destroy()
                            timer.destroy()

                        timer.withdraw()
                        time_up = tk.Toplevel(root)  # Create time-up window
                        time_up.geometry("460x240")
                        time_up.resizable(False, False)
                        time_up.title("Timer")
                        time_up.configure(bg = "LightSkyBlue1")
                        time_up.protocol("WM_DELETE_WINDOW", end)
                        space = tk.Label(time_up, text=" ").grid(row=0)
                        time_label3 = tk.Label(time_up, text="Time's up!", font=("Arial Black", 60), bg = "LightSkyBlue1").place(relx=0.5, rely=0.4, anchor="center")
                        cont = tk.Button(time_up, text="Continue", font=("Arial"), command=cont).place(relx=0.3, rely=0.8, anchor="center")
                        end = tk.Button(time_up, text="End", font=("Arial"), command=end).place(relx=0.7, rely=0.8, anchor="center")

                        def sound():
                            winsound.Beep(1000, 500)
                            time_up.after(1000, sound)
                            
                        sound()

                def pause():
                    self.paused = True
                    pause_btn.config(state="disabled")
                    continue_btn.config(state="normal")
                
                def continue_timer():
                    self.paused = False
                    pause_btn.config(state="normal")
                    continue_btn.config(state="disabled")
                    timer_count()  # Resume the countdown immediately

                def end():
                    self.paused = False
                    self.root.attributes("-disabled", False) 
                    timer.destroy()
                    
                # Pause, Continue, and End Buttons
                pause_btn = tk.Button(timer, text="Pause", font=("Arial"), command=pause, state="normal")
                pause_btn.place(relx=0.3, rely=0.9, anchor="center")
                continue_btn = tk.Button(timer, text="Continue", font=("Arial"), command=continue_timer, state="disabled")
                continue_btn.place(relx=0.5, rely=0.9, anchor="center")
                end_btn = tk.Button(timer, text="End", font=("Arial"), command=end)
                end_btn.place(relx=0.7, rely=0.9, anchor="center")

                # Handle window close (X button)
                timer.protocol("WM_DELETE_WINDOW", end)
                timer_count()  # Start the countdown
                
        def on_close(self):
            root.deiconify()  # Show the main window
            self.root.destroy()  # Close the TimerApp window
    
    alarm_root = tk.Toplevel()
    TimerApp(alarm_root)
    
def on_icon_click(icon_name):
    if icon_name == "Pomodoro":
        pomodoroFunction(root)
        
    elif icon_name == "AlarmClock":
        alarmClockFunction()
        
    else:
        timerFunction() 

# Initialize the main window
root = tk.Tk()  # Create main window
root.title("AMCS1034 - Personal Assistant Software")
root.geometry("400x300")  # Set the window size


# Create a menu bar
menu_bar = tk.Menu()  # Create menu bar

def help_function():
    messagebox.showinfo("About", "AMCS1034 - Personal Assistant Software - By Ern Hong, Zhen Yi, Shen Chung.")

# Add a Help menu
help_menu = tk.Menu(menu_bar, tearoff = 0)
help_menu.add_command(label = "About", command = help_function)  # Reference the function
menu_bar.add_cascade(label = "Help", menu = help_menu)

# Attach the menu bar to the root window
root.config(menu = menu_bar)

# Create a frame for the icons
icon_frame = ttk.Frame(root, padding = 10)
icon_frame.pack(fill = tk.BOTH, expand = True)

# Define a helper function to load and resize images
def load_resized_image(path, width, height):
    pil_image = Image.open(path).resize((width, height), Image.Resampling.LANCZOS)
    return ImageTk.PhotoImage(pil_image)

# Load and resize the images
icons = {
    "Pomodoro": load_resized_image("Images/pomodoro.png", 50, 50),
    "AlarmClock": load_resized_image("Images/alarm-clock.png", 50, 50),
    "Timer": load_resized_image("Images/alarm.png", 50, 50),
}

# Define a helper function to bind the icon name
def create_button_command(icon_name):
    def command():
        on_icon_click(icon_name)
    return command

# Add icons and labels to the frame
for icon_name in icons:
    # Create a sub-frame for each icon
    sub_frame = ttk.Frame(icon_frame, padding = 5)
    sub_frame.pack(side = tk.LEFT, padx = 10, pady = 5, anchor = tk.N)  # Align the sub-frame to the top

    # Create and pack the button with the icon
    icon_button = ttk.Button(sub_frame, image = icons[icon_name], command = create_button_command(icon_name))
    icon_button.image = icons[icon_name]  # Prevent garbage collection
    icon_button.pack(pady = (0, 5))  # Add less padding below the button

    # Create and pack the label under the icon
    icon_label = ttk.Label(sub_frame, text = icon_name)
    icon_label.pack()

# Start the GUI event loop
root.mainloop() 