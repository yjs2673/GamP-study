jobs = [
    (1, 0, 6),   # 작업 1: 시작 0, 종료 6
    (2, 1, 4),   # 작업 2: 시작 1, 종료 4
    (3, 3, 5),   # 작업 3: 시작 3, 종료 5
    (4, 5, 7),   # 작업 4: 시작 5, 종료 7
    (5, 8, 9),   # 작업 5: 시작 8, 종료 9
]

def schedule_jobs(jobs):
    # 1. 종료 시간을 기준으로 정렬
    sorted_jobs = sorted(jobs, key=lambda x:x[2]) # blank

    selected_jobs = []  # 선택된 작업
    last_finish_time = 0  # 마지막으로 선택된 작업의 종료 시간

    # 2. 각 작업을 확인
    for job in sorted_jobs:
        start, finish = job[1], job[2]

        # 3. 현재 작업이 마지막 선택된 작업과 겹치지 않으면 선택
        if last_finish_time <= start:   # blank 
            selected_jobs.append(job)
            last_finish_time = finish   # blank

    return selected_jobs

result = schedule_jobs(jobs)

print("선택된 작업들:")
for job in result:
    print(f"작업 번호: {job[0]}, 시작 시간: {job[1]}, 종료 시간: {job[2]}")
