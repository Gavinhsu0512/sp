# do_while_example.py

def do_while_example():
    count = 0
    while True:
        print(f"計數為: {count}")
        count += 1
        if not (count < 5):
            break

if __name__ == "__main__":
    do_while_example()
