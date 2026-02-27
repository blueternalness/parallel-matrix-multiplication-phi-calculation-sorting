import matplotlib.pyplot as plt

# Actual experimental data
threads = [1, 4, 16, 64, 256]
time_version_a = [252.09, 15.63, 11.74, 11.34, 11.83]
time_version_b = [16.71, 4.62, 3.16, 3.64, 3.51]
time_version_c = [12.56, 3.45, 2.16, 2.11, 2.11]

# Initialize the plot
plt.figure(figsize=(10, 6))

# Plot the three versions with distinct markers and colors
plt.plot(threads, time_version_a, marker='o', linestyle='-', color='red', label='Version A (Naive)')
plt.plot(threads, time_version_b, marker='s', linestyle='-', color='blue', label='Version B (Blocked)')
plt.plot(threads, time_version_c, marker='^', linestyle='-', color='green', label='Version C (Transposed)')

# Ensure the x-axis ticks match the specific thread counts
plt.xticks(threads, labels=[str(t) for t in threads])

# Titles and labels (removed "Log Scale" from labels)
plt.title('Execution Time by Number of Threads', fontsize=14)
plt.xlabel('Number of Threads', fontsize=12)
plt.ylabel('Execution Time (sec)', fontsize=12)

# Styling
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend(fontsize=12)
plt.tight_layout()

# Save the output image to be used by LaTeX
plt.savefig('performance_scaling.png', dpi=300)
print("Plot successfully saved as 'performance_scaling.png'.")

# Display the plot in the window
plt.show()