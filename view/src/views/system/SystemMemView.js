import {DECIMAL_POINTS} from "../../config"

import { DataGrid } from '@mui/x-data-grid';

import ExpandedForm from '../ExpandedForm';

export const SystemMemView = ({data, totalMemory, totalSwap}) => {

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

    const main_items = Object.keys(data.main).map( (key, i) => 
        ({id: i, name: key, absolute: data.main[key], relative: data.main[key] / totalMemory * 100})
    )

    const swap_items = Object.keys(data.swap).map( (key, i) => 
        ({id: i, name: key, absolute: data.swap[key], relative: data.swap[key] / totalSwap * 100})
    )

    return (
        <div>
            
            <ExpandedForm title="Основна">
                <DataGrid
                    rows={main_items}
                    columns={columns}
                    hideFooter={true}
                />
            </ExpandedForm>
            <ExpandedForm title="Свап">
                <DataGrid
                    rows={swap_items}
                    columns={columns}
                    hideFooter={true}
                />
            </ExpandedForm>
        </div>
    );
  };
  
  export default SystemMemView;