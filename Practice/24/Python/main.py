import json
completeDict = {}

with open("in.json") as json_data:
    in_data = json.load(json_data)

    for task in in_data:
        if task["completed"]:

            if not task["userId"] in completeDict:
                completeDict[task["userId"]] = 0

            completeDict[task["userId"]] += 1

out = []

for id, counted in completeDict.items():
    out.append({ "userId": id, "task_completed": counted })

with open('out.json', 'w') as out_json:
    json.dump(out, out_json)