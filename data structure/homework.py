import json
import math
import re
from collections import Counter
import time

## 정규표현식을 위한 WORD
WORD = re.compile(r"\w+")

# 데코레이터 위한  타이머 함수
def timer(fn):
    def inner(*args, **kwargs):
      start_time = time.time()
      fn(*args, **kwargs)
      elapsed = time.time() - start_time
      print("execution time : {}".format(elapsed*1000))
    return inner

# OCP 요구사항
# LDM 과 함께 데이터 추가 및 검색, 삭제의 예제로써 loads(filename) 
# search(attribute, target), delete(target) 함수를 갖는다. 예로, loads는 LDM의 store_lectures_from_json를 내부적으로(internally) 호출한다
class OCP:
  def __init__(self): # 생성자 통해 ocp instance 생성시 imdf, ldm, lr, pm class의 인스턴스를 생성합니다.
    self.imdf = IMDF()
    self.ldm = LDM()
    self.lr = LR()
    self.pm = PM()
  # 강의 수집
  @timer
  def load_lectures(self, filename):
    self.ldm.store_lecture_from_json(filename, self.imdf)
  # 강의 검색
  @timer
  def search_lecture(self, attribute, target):
    print(self.ldm.search(attribute, target, self.imdf))
  # 강의 삭제
  @timer
  def delete_lecture(self, target):
    self.ldm.delete(target, self.imdf)
  # 강의 출력
  @timer
  def print_lecture(self):
    self.ldm.print_lecture(self.imdf)
  # 강의 추천
  @timer
  def recommend_lecture(self, attribute, target, count):
    search_result = self.ldm.search(attribute, target, self.imdf)
    self.lr.recommend_lectures(search_result,count, self.imdf)
  # 강의 추천 (원형 큐)
  @timer
  def recommend_lecture_using_circular_queue(self, attribute, target, count):
    search_result = self.ldm.search(attribute, target, self.imdf)
    self.lr.recommend_lectures_using_circular_queue(search_result, count, self.imdf)
    

class PM:
  def __init__(self):
    pass
  
  @timer
  def monitor(self,fn):
    def inner(*args, **kwargs):
      fn(*args, **kwargs)
    return inner


# 강의 추천을 위한 원형 큐 자료구조
class CircularQueue:
  def __init__(self, maxSize):
    self._count = 0
    self._front = 0
    self._back = maxSize - 1
    self._qArray = [0]*maxSize

  def isEmpty(self):
    return self._count == 0
  
  def isFull(self):
    return self._count == len(self._qArray)
  
  def enqueue(self, item):
    if self.isFull():
      return
    maxSize = len(self._qArray)
    self._back = (self._back + 1) % maxSize # back 이동
    self._qArray[self._back] = item # 이동된 back에 item 넣어줌
    self._count += 1
  
  def dequeue(self):
    if self.isEmpty():
      return
    item  = self._qArray[self._front]
    maxSize = len(self._qArray)
    self._front = (self._front + 1) % maxSize # front 이동
    self._count -= 1 # 원형 큐의 갯수 낮춰줌
    return item
  def print_queue(self): # queue가 빌때까지 dequeue 해서 출력
    while self.isEmpty() != True:
      print(self.dequeue())



# Lecture 요구 사항
# 정보 교환을 위한 기본 데이터 모델
#  print(lecture)하면 강좌 아이디, 강좌명, 강좌 url 출력
# SLL 기반의 노드임, 
class Lecture:
  def __init__(self, blocks_url, id, name,short_description,link):
    self.blocks_url = blocks_url # 강좌 url
    self.id = id # 강좌 id
    self.name = name # 강좌명
    self.short_description = short_description # 짧은 소개
    self.next = link # 다음 node에 대한 link
  def __str__(self):
    return f"강좌아이디: {self.id}, 강좌명: {self.name}, 강좌URL: {self.blocks_url}"

# IMDF 요구사항
# 다수의 강좌를 포함하는 데이터 컨테이너
# 강좌의 시작을 가리키는 head reference 가짐 (첫번재 강좌)
class IMDF:
  def __init__(self):
    self.head = None

# LDM 클래스 요구사항
# 강좌 데이터에 대한 추가, 검색, 삭제가 가능해야 한다.
# 추가 기능: json 파일을 읽어 IMDF 클래스의 인스턴스에 저장하는 store_lecture_from_json 함수 
# 검색 기능: SLL 기반 IMDF 내 강좌로 부터 속성과 그 에대한 값을 검색하는 함수
# 삭제 기능: SLL 기반 IMDF 내 강좌로 부터 특정 강좌명을 삭제하는 함수를 작성
class LDM:
  def __init__(self):
    pass

  # json 파일을 읽어 IMDF 클래스의 인스턴스에 저장
  def store_lecture_from_json(self, filename, imdf):
    lectures=""
    with open(filename, 'r', encoding="UTF-8") as f:
      lectures = json.load(f)
    for i in range(0, len(lectures)):
      if imdf.head is None: # 리스트가 비었을 경우 (첫 시작) 0번 index의 item을 넣어 줍니다.
        imdf.head = Lecture(lectures[0]['blocks_url'], lectures[0]['id'], lectures[0]["name"],lectures[0]["short_description"], None)
      else: 
        imdf.head = Lecture(lectures[i]['blocks_url'], lectures[i]['id'], lectures[i]["name"],lectures[i]["short_description"] ,imdf.head)
  def search(self,attribute,target,imdf): # SLL 기반 IMDF 내 강좌로부터 특정 속성과 그에 대한 값을 검색 함수를 작성하시오. 
    if imdf.head is None:
      print("저장된 데이터가 없음")
      return
    else:
      link = imdf.head  # 처음은 head를 지정. 이후부터는 현 노드의 next를 지정
      if attribute == "강좌명": # attribute 를 받아서 강좌명 혹은 url로 검색할 수 있습니다.
        while link:
          if target == link.name: # 강좌명을 찾으면 해당 node를 return
            return link
          else:
            link = link.next
      else: # url로 검색
        while link:  
          if target == link.blocks_url: # 해당하는 url을 찾으면 해당 node를 return
            return link
          else:
            link = link.next
      print("일치되는 값이 없습니다.")
  def delete(self, target, imdf): # 강좌명을 target으로 받아서 리스트에서 삭제하는 함수
    if imdf.head is None:
      print("저장된 데이터가 없음")
      return
    else:
      link = imdf.head
      prev = link # 삭제하려면 이전노드와 이어줘야하므로 prev node 에대한 정보가 필요합니다.
      while link:
        if link.name == target:
          prev.next = link.next # target을 찾을 경우 이전 노드와 해당 노드(link)의 next를 이어 줍니다, 파이썬에서는 gc(garbage collection) 에 의해 사용되지 않는 노드는 삭제됩니다.
          return
        else:
          prev = link # target이 아닐경우 prev에 노드를 저장하고 link를 next 해줍니다.
          link = link.next  

  def print_lecture(self, imdf):
    if imdf.head is None:
      print("저장된 데이터가 없음")
      return
    else:
      link = imdf.head #처음은 head를 지정. 이후부터는 현 노드의 next를 지정
      #link가 가리키는 노드가 없을 때까지 반복
      #None,0,""는 조건판단에서 False 처리, 그 외는 True로 처리된다.
      while link :
        print(link)
        link = link.next #link를 현 위치 노드의 next로 변경
      print() #줄바꿈 용



class LR:
  def __init__(self):
    pass

  def get_cosine_simiarity(self,vec1, vec2): # Worst-Case Time Complexity O(N^2)
    '''
    코사인 값을 가져오는 함수
    @vec1: 벡터 1
    @vec2: 벡터 2
    '''
    intersection = set(vec1.keys()) & set(vec2.keys())
    numerator = sum([vec1[x] * vec2[x] for x in intersection]) # x 에 대한 vec1[x] * vec2[x] 값의 리스트의 합이므로 x => len(intersection)번 순회 하니까 O(n^2)
    sum1 = sum([vec1[x] ** 2 for x in list(vec1.keys())]) 
    sum2 = sum([vec2[x] ** 2 for x in list(vec2.keys())])
    denominator = math.sqrt(sum1) * math.sqrt(sum2)
    if not denominator:
      return 0.0
    else:
      return float(numerator) / denominator
  def text_to_vector(self,text):
      '''
      텍스트를 단어(word)로 나눈뒤, 각 단어별로 카운터하여 Dict 형태로 저장
      @text : 텍스트
      '''
      words = WORD.findall(text)
      return Counter(words)
  def recommend_lectures(self,lec, k, imdf):
    input_vector = self.text_to_vector(lec.short_description) # 함수의 파라미터로 받은 lec의 short_description을 벡터화
    cosine_list = [] # 코사인 값을 저장할 리스트 
    if imdf.head is None:
      print("저장된 데이터가 없음")
      return
    else:
      link = imdf.head #처음은 head를 지정. 이후부터는 현 노드의 next를 지정
      while link :
        if link.id == lec.id:
          cosine_list.append([link,-1]) # consine_list = [lec 객체, cosine 값], 현재 노드의 경우는 제외해야하므로 제일 낮은 cosine 값인 -1을 줌
          link = link.next
        else:
          target_vector = self.text_to_vector(link.short_description) # 비교할 target link의 short_description을 vector 화
          cosine = self.get_cosine_simiarity(input_vector, target_vector) # 코사인 값 계산
          cosine_list.append([link,cosine]) # 코사인 리스트에 추가
          link = link.next #link를 현 위치 노드의 next로 변경
      cosine_list.sort(key=lambda x: -x[1]) # cosine 값을 기준으로 내림차순 정렬
      for i in range(k): # k 개 만큼 출력
        print(cosine_list[i][0])
  def recommend_lectures_using_circular_queue(self, lec, k ,imdf):
    input_vector = self.text_to_vector(lec.short_description)
    cosine_list =[] # 후보 코사인 리스트
    if imdf.head is None:
      print("저장된 데이터가 없음")
      return
    else:
      link = imdf.head #처음은 head를 지정. 이후부터는 현 노드의 next를 지정
      while link :
        if link.id == lec.id:
          link = link.next
        else:
          target_vector = self.text_to_vector(link.short_description)
          cosine = self.get_cosine_simiarity(input_vector, target_vector)
          if cosine >= 0.005: # 코사인 값이 0.005 이상만 후보군 list에 추가 
            cosine_list.append([link,cosine])
          link = link.next #link를 현 위치 노드의 next로 변경

      # cosine_list.sort(key=lambda x: -x[1]) #4의 경우 내림차순 정렬을 하지 않고 k개 혹은 m개의 강좌만 원형큐에 넣는 것으로 이해했습니다.
      cq = CircularQueue(k)
      for i in range(len(cosine_list)):
        if i >= k : # k개의 강좌만 enqueue하고 나머지는 버린다.
          break
        cq.enqueue(cosine_list[i][0])
        
      cq.print_queue()




def main():
  ocp = OCP()
  print("### json file load ###")
  ocp.load_lectures('lectures.json')
  print() # 공백용 출력
  print("### delete lecture ###")
  ocp.delete_lecture("우리말 형태론")
  print() # 공백용 출력
  print("### search lecture ###")
  ocp.search_lecture("강좌명", "정보통신 보안")
  print() # 공백용 출력
  #print("### print All lecture ###")
  #ocp.print_lecture()
  #print() # 공백용 출력
  print("### recommend lecture ###")
  ocp.recommend_lecture("강좌명", "베이비시터, '함께 키움'의 세상 만들다", 3)
  print() # 공백용 출력
  print("### recommend lecture using circular queue ###")
  ocp.recommend_lecture_using_circular_queue("강좌명", "베이비시터, '함께 키움'의 세상 만들다", 3)
  print() # 공백용 출력


main()