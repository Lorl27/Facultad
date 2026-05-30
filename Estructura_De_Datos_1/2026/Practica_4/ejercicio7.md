```plantuml
@startuml
skinparam packageStyle rectangle

object 10
object 20
object 25
object 30
object 15
object 16
object 18
object 19

10 --> 20 : der
20 --> 25 : der
25 --> 30 : der
20 --> 15 : izq
15 --> 16 : der
16 --> 18 : der
18 --> 19 : der
@enduml
