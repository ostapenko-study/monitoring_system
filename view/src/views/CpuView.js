import {DECIMAL_POINTS} from "../config"


import { DataGrid } from '@mui/x-data-grid';

export const CpuView = ({data, totalCpu}) => {

    const items = Object.keys(data).map( (key, i) => 
      ({id: i, name: key, absolute: data[key], relative: data[key] / totalCpu * 100})
    )

    const columns = [
      {
        field: 'name',
        headerName: 'name',
        type: 'string',
        width: 160,
      },
      {
        field: 'absolute',
        headerName: 'absolute (processor ticks)',
        type: 'number',
        width: 400,
      },
      {
        field: 'relative',
        headerName: 'relative (%)',
        type: 'number',
        valueGetter: (value, row) => Number(row.relative).toFixed(DECIMAL_POINTS),
        width: 400,
      }
    ]
    return (
      <DataGrid
        rows={items}
        columns={columns}
        hideFooter={true}
      />
    );
  };
  
  export default CpuView;