package com.reliability.service;

import com.alibaba.excel.context.AnalysisContext;
import com.alibaba.excel.event.AnalysisEventListener;
import com.reliability.dto.DataBaseDTO;
import com.reliability.dto.TextDTO;
import com.reliability.entity.SourceData;
import com.reliability.exception.CustomException;
import com.reliability.repository.DataRepository;
import com.reliability.vo.DataRespVO;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

@Service
public class DataService {

    @Value("${file.suffix}")
    private ArrayList<String> fileSuffix;
    //private final UserService userService;
    private final DataRepository dataRepository;

    public DataService(DataRepository dataRepository) {
        //this.userService = userService;
        this.dataRepository = dataRepository;
    }

    public List<Double> getSource(String uuid) throws Exception {
        var source = this.dataRepository.findAllByUuid(uuid);
        if (source.size() == 0) {
            throw new Exception("not found");
        }
        var list = new ArrayList<Double>();
        for (var sourceData : source) {
            list.add(sourceData.getGaps());
        }
        return list;
    }

    public DataRespVO db(DataBaseDTO dataBaseDTO) {
        var uuid = UUID.randomUUID().toString();
        //var user = this.userService.getMe();
        var lines = new ArrayList<SourceData>();
        switch (dataBaseDTO.getType()) {
            case MYSQL:
                try {
                    var url = "jdbc:mysql://" + dataBaseDTO.getHost() + ":" + dataBaseDTO.getPort() + "/" + dataBaseDTO.getDatabase();
                    var conn = DriverManager.getConnection(url, dataBaseDTO.getUsername(), dataBaseDTO.getPassword());
                    var stmt = conn.createStatement();
                    var rs = stmt.executeQuery("select * from " + dataBaseDTO.getTable());
                    while (rs.next()) {
                        lines.add(SourceData.builder()
                                //.userId(user.getId())
                                .times(rs.getLong("times"))
                                .gaps(rs.getDouble("gaps"))
                                .uuid(uuid)
                                .build());
                    }
                    this.dataRepository.saveAll(lines);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                    throw new CustomException(HttpStatus.BAD_REQUEST, "failed to load data from database");
                }
                break;
            case POSTGRES:
                break;
        }
        return new DataRespVO(uuid, lines);
    }

    public DataRespVO text(TextDTO text) {
        var uuid = UUID.randomUUID().toString();
        //var user = this.userService.getMe();
        var in = new BufferedReader(new StringReader(text.getText()));
        var lines = new ArrayList<SourceData>();
        String line;
        try {
            while (in.ready()) {
                line = in.readLine();
                if (null == line) break;
                var l = line.split("[ \t]");
                lines.add(SourceData.builder()
                        .userId(new Long(1))
                        .times(Long.parseLong(l[0]))
                        .gaps(Double.parseDouble(l[1]))
                        .uuid(uuid)
                        .build());
            }
            this.dataRepository.saveAll(lines);
        } catch (IOException e) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "failed to save text");
        }
        return new DataRespVO(uuid, lines);
    }

    public DataRespVO file(MultipartFile file) {
        var filename = file.getOriginalFilename();
        if (filename == null) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "filename does not exist");
        }
        var dotIndex = filename.lastIndexOf(".");
        if (dotIndex == -1) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "file type incorrect");
        }
        var suffix = filename.substring(dotIndex + 1).toLowerCase();
        if (!this.fileSuffix.contains(suffix)) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "file type incorrect");
        }
        var uuid = UUID.randomUUID().toString();
        //var user = this.userService.getMe();
        var lines = new ArrayList<SourceData>();
        try {
            switch (suffix) {
                case "txt":
                    var in = new BufferedReader(new InputStreamReader(file.getInputStream()));
                    String line;
                    while (in.ready()) {
                        line = in.readLine();
                        var l = line.split("\t");
                        lines.add(SourceData.builder()
                                //.userId(user.getId())
                                .times(Long.parseLong(l[0]))
                                .gaps(Double.parseDouble(l[1]))
                                .uuid(uuid)
                                .build());
                    }
                    this.dataRepository.saveAll(lines);
                    break;
                case "xls":
                case "xlsx":
//                EasyExcel.read(file.getInputStream(), , );
            }
        } catch (IOException e) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "failed to store file");
        }
        return new DataRespVO(uuid, lines);
    }
}

class SData {
    private Long times;
    private Long gaps;
}

class SDataListener extends AnalysisEventListener<SData> {

    @Override
    public void invoke(SData data, AnalysisContext context) {

    }

    @Override
    public void doAfterAllAnalysed(AnalysisContext context) {

    }
}
