import os

sources = {}

Import("c_state_env")

objects = [c_state_env.Object(x) for x in Glob("./src/*.c")]

result = (objects, list(map(lambda x: os.path.join(os.getcwd(), x), ["src"])))
Return("result")
