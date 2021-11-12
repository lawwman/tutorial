import subprocess

result = subprocess.run("cd ..", shell=True, capture_output=True)
print("stdout:", result.stdout)
print("stderr:", result.stderr)