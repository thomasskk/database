import subprocess


def capture(command):
    proc = subprocess.Popen(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True
    )
    out, err = proc.communicate()
    return out, err, proc.returncode


def test():
    command = ["./main.out", "insert 1 user1 person1@example.com"]
    out, err, exitcode = capture(command)
    assert out == b""
