
#pragma once

const uint32_t SECOND = 1000u;
const uint32_t MINUTE = 60 * SECOND;

class QueryManager {
  public:
    QueryManager(uint32_t queryPeriod)
      : queryPeriod(queryPeriod)
      , lastQueryTime(-queryPeriod)
    {}

    template <typename Q>
    void query(Q doQuery, bool force = false) {
      const long now = millis();
      if (force || now - lastQueryTime > queryPeriod) {
        if (doQuery()) {
          lastQueryTime = now;
        }
      }
    }

  private:
    uint32_t queryPeriod;
    uint32_t lastQueryTime;
};

