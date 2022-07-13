'''
as475
Akash 
Sharma
'''


from pyspark.sql import SparkSession
from pyspark import SparkConf, SparkContext
import sys
import time


#Below method is used to split the line in to source and Target
def splitST(line):
    fields = line.split(" ")
    Source = int(fields[0])
    Target = int(fields[1])
    return (Source, Target)


#Below is the main method read the text file.
if __name__ == "__main__":
    conf = SparkConf().setMaster("local[*]").setAppName("find the root")
    sc = SparkContext(conf = conf)
    sc.setLogLevel("ERROR")
    StartTime = time.time()
    lines = sc.textFile(sys.argv[1])
    rdd = lines.map(splitST)
    length=rdd.count()
    #print(rdd.collect())
    root = rdd.filter(lambda x:x[0] == x[1])
    reverserdd = rdd.map(lambda x: (x[1],x[0]))
    #print(reverserdd.collect())

    while True:
        root = root.join(reverserdd).groupByKey().mapValues(tuple).flatMap(lambda x:x[1]).map(lambda x: (x[1],x[0]))
        if root.count() == length:
            break




    #answer=root.collect()
    root.coalesce(1).saveAsTextFile(sys.argv[2])
    sc.stop()
    print("time : ", time.time()-StartTime)