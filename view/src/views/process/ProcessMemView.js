import {DECIMAL_POINTS} from "../../config"

import { DataGrid } from '@mui/x-data-grid';

export const ProcessMemView = ({data, totalMemory, totalSwap}) => {

    const columns = [
        {
          field: 'name',
          headerName: 'name',
          type: 'string',
          width: 160,
        },
        {
          field: 'absolute',
          headerName: 'absolute (Kb)',
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

    const items = [
        {
            id: 1,
            name: "data",
            absolute: data.data,
            relative: Number(data.data / totalMemory * 100).toFixed(DECIMAL_POINTS),
        },
        {
            id: 2,
            name: "stk",
            absolute: data.stk,
            relative: Number(data.stk / totalMemory * 100).toFixed(DECIMAL_POINTS),
        },
        {
            id: 3,
            name: "exe",
            absolute: data.exe,
            relative: Number(data.exe / totalMemory * 100).toFixed(DECIMAL_POINTS),
        },
        {
            id: 100000,
            name: "swap",
            absolute: data.swap,
            relative: Number(data.swap / totalSwap * 100).toFixed(DECIMAL_POINTS),
        }
    ]

    console.log(data)

    return (
        <DataGrid
            rows={items}
            columns={columns}
            hideFooter={true}
        />
    );
  };
  
  export default ProcessMemView;