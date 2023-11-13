package com.reliability.repository;

import com.reliability.entity.SourceData;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface DataRepository extends JpaRepository<SourceData, Long> {
    List<SourceData> findAllByUuid(String uuid);
}
