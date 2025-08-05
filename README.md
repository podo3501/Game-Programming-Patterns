이 프로젝트는 C++을 기반으로 하여, 테스트 주도 개발(TDD) 방식으로 설계되었습니다.  
다양한 디자인 패턴을 게임 시스템에 실용적으로 적용하면서, 성능 최적화와 유지보수성을 함께 고려한 아키텍처를 구축하는 것을 목표로 합니다.

- 명령 처리 및 입력 시스템  
  Command Pattern: 키 매핑, Undo 기능 구현 등으로 사용 (툴/게임 양쪽)  
  
- 상태 및 이벤트 처리  
  State Pattern: 캐릭터 상태 변화 모델링  
  Observer Pattern: 도전 과제 같은 이벤트 발생 감지 및 반응 처리  
  Event Queue Pattern: 사운드 출력을 비동기로 처리  
  
- 객체 생성 및 관리  
  Prototype Pattern: 몬스터 스폰을 복제 기반으로 처리  
  Object Pool Pattern: 파티클 풀 메모리 단편화 최소화  
  Type Object Pattern: 종족을 json 기반으로 다양하게 생성  
  
- 성능 최적화  
  Spatial Partition Pattern: 다수 캐릭터의 충돌/상호작용을 구역 단위로 분할  
  Data Locality Pattern: 캐시 적중률을 높이기 위한 파티클 시스템 구성  
  Dirty Flag Pattern: 값이 변경되었을 때만 재계산하여 성능 최적화  
  Flyweight Pattern: 2D 지형 정보의 메모리 효율화  
  
- 서비스 및 시스템 구조  
  Service Locator / Mediator Pattern: 전역 접근 가능한 서비스 구조 설계  
  Decorator Pattern: 로깅 등 런타임 기능 추가  
  
- 스크립팅 및 표현  
  Bytecode Pattern: 기획자가 사용할 수 있는 간단한 스크립트 언어 도입  
  nlohmann json 도입: Type Object 등 데이터 직렬화를 위한 외부 라이브러리 통합  
